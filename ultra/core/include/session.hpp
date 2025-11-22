#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP
#include "idriver.hpp"
#include <iostream>
#include "mysql_dialect.hpp"
#include "create_table_query_builder.hpp" 
#include "select_query_builder.hpp"
#include "insert_query_builder.hpp"
#include "update_query_builder.hpp"
#include "sql_dialect.hpp"
#include "mysql_result_set.hpp"
#include "relation.hpp"
#include "aggregate.hpp"
#define DEBUG
namespace quick {
namespace ultra {

inline std::string to_connection_string(const std::string& host, const std::string& user, const std::string& pass, const std::string& dbnm, int port = 3306){
    return "host=" + host + ";user=" + user + ";password=" + pass + ";database=" + dbnm;
}


class Session {
public:
    explicit Session(std::shared_ptr<IDriver> driver);

    template <typename TBL>
    std::shared_ptr<TBL> get_by_id(int id) {
        static_assert(std::is_base_of_v<quick::ultra::sqljke::SQLTable, TBL>, "Template argument must derive from SQLTable");

        auto select = std::make_unique<sqljke::SelectQueryBuilder>(dialect_.get());

        std::string sql = select->from(TBL().table_name()).where("id = " + std::to_string(id)).build();

#ifdef DEBUG
        std::cout << "Executing SQL: " << sql << std::endl;
#endif
        try {
            ResultSetPtr result = driver_->query(sql);

            if (!result || !result->next()) {
                return nullptr;
            }

            auto obj = std::make_shared<TBL>(*result);
            return obj;

        } catch (const std::exception& e) {
            std::cerr << "Exception during get(): " << e.what() << std::endl;
            return nullptr;
        }
    }
    
    template <typename TBL>
    std::vector<std::shared_ptr<TBL>> get_all(std::vector<sqljke::Expression> where = {}, int limit = -1, int offset = -1) {
        static_assert(std::is_base_of_v<sqljke::SQLTable, TBL>, "Template argument must derive from SQLTable");

        auto select = std::make_unique<sqljke::SelectQueryBuilder>(dialect_.get());
        std::string table_name = TBL::TABLE_NAME;
        auto sql_builder = select->from(table_name);

        if (!where.empty()) {
            for(auto cl : where){
                sql_builder = sql_builder.where(cl);
            }
        }

        if (limit > 0) {
            sql_builder = sql_builder.limit(limit);
            if (offset > 0) {
                sql_builder = sql_builder.limit(limit, offset);
            }
        }

        std::string sql = sql_builder.build();

#ifdef DEBUG
        std::cout << "Executing SQL: " << sql << std::endl;
#endif

        std::vector<std::shared_ptr<TBL>> result;

        try {
            ResultSetPtr rs = driver_->query(sql);
            if (!rs) return result;

            while (rs->next()) {
                auto obj = std::make_shared<TBL>(*rs); 
                result.push_back(obj);
            }

        } catch (const std::exception& e) {
            std::cerr << "Exception during get_all(): " << e.what() << std::endl;
        }

        return result;
    }

    template <typename TBL>
    void save(const std::shared_ptr<TBL>& obj) {
        static_assert(
            std::is_base_of_v<sqljke::SQLTable, TBL>,
            "TBL must derive from SQLTable"
        );

        if (!obj) return;

        for (const auto& dep : obj->get_dependent_objects()) {
            if (dep->id() == 0) {
                save(dep); 
            }
        }

        if (obj->id() != 0) {
            do_update(obj);
        } else {
            do_insert(obj);
        }
    }
    

    sqljke::CreateTableQueryBuilder& create_table(const std::string& table_name);
    sqljke::SelectQueryBuilder& select(const std::vector<sqljke::Column>& columns);
    sqljke::SelectQueryBuilder& select(const sqljke::Aggregate& aggregate);
    sqljke::UpdateQueryBuilder& update(const std::string& table_name);
    sqljke::InsertQueryBuilder& insert_into(const std::string& table_name);

    void create_tables(std::vector<std::shared_ptr<sqljke::SQLTable>> tables);

    ResultSetPtr execute(const std::string& sql);

    //future
    void delete_from();
    void drop_table();
    void table_exists();
    void truncate_table();
    void drop_database(const std::string& database_name);
    

private:
    std::shared_ptr<IDriver> driver_;
    std::unique_ptr<sqljke::ISQLDialect> dialect_;

    sqljke::SelectQueryBuilder select_;
    sqljke::CreateTableQueryBuilder create_;
    sqljke::InsertQueryBuilder insert_;
    sqljke::UpdateQueryBuilder update_;


    template <typename TBL>
    void do_insert(const std::shared_ptr<TBL>& obj) {
        try {
            std::string sql = insert_
                .set_table(obj->table_name())
                .columns(obj->column_names())
                .values(obj->values())
                .build();

            std::cout << "Executing SQL: " << sql << std::endl;

            execute(sql);
            int inserted_id = driver_->get_last_insert_id();
            obj->set_id(inserted_id);

#ifdef DEBUG
            std::cout << "Saved " << obj->table_name() << " with id=" << inserted_id << std::endl;
#endif

        } catch (const std::exception& e) {
            std::cerr << "Exception during INSERT: " << e.what() << std::endl;
        }
    }

    template <typename TBL>
    void do_update(const std::shared_ptr<TBL>& obj) {
        try {
            auto update_builder = update(obj->table_name());
            const auto& cols = obj->column_names();
            const auto& vals = obj->values();

            for (size_t i = 0; i < cols.size(); ++i) {
                update_builder.set(cols[i], vals[i]);
            }

            std::string sql = update_builder.where("id = " + std::to_string(obj->id())).build();

            std::cout << "Executing SQL: " << sql << std::endl;

            execute(sql);

#ifdef DEBUG
            std::cout << "Updated " << obj->table_name() << " with id=" << obj->id() << std::endl;
#endif

        } catch (const std::exception& e) {
            std::cerr << "Exception during UPDATE: " << e.what() << std::endl;
        }
    }
};

}}// namespace quick::ultra

#endif
