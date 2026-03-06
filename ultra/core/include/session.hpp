#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP
#include "idriver.hpp"
#include <iostream>
#include "mysql_dialect.hpp"
#include "create_table_query_builder.hpp" 
#include "select_query_builder.hpp"
#include "insert_query_builder.hpp"
#include "update_query_builder.hpp"
#include "delete_query_builder.hpp"
#include "sql_dialect.hpp"
#include "mysql_result_set.hpp"
#include "relation.hpp"
#include "aggregate.hpp"
#include "status.hpp"
#define DEBUG
namespace quick {
namespace ultra {

inline std::string to_connection_string(const std::string& host, const std::string& user, const std::string& pass, const std::string& dbnm, int port = 3306){
    return "host=" + host + ";user=" + user + ";password=" + pass + ";database=" + dbnm;
}


class Session {
public:
    explicit Session(std::shared_ptr<IDriver> driver);

    ResultSetPtr execute(const std::string& sql);

    Status create_tables(std::vector<std::shared_ptr<sqljke::SQLTable>> tables);
    sqljke::CreateTableQueryBuilder& create_table(const std::string& table_name);

    template <typename TBL>
    Status save(const std::shared_ptr<TBL>& obj) {
        static_assert(std::is_base_of_v<sqljke::SQLTable, TBL>, "TBL must derive from SQLTable");
        if (!obj) return FAIL;

        for (const auto& dep : obj->get_dependent_objects()) {
            if (dep) {
                save(dep); 
            }else{
                std::cout << "unknown" << std::endl;
            }
        }

        if (obj->id() != 0) {
            do_update(obj);
        } else {
            do_insert(obj);
        }
        return OK;
    }
    sqljke::InsertQueryBuilder& insert_into(const std::string& table_name);

    template <typename TBL>
    std::variant<std::shared_ptr<TBL>, std::vector<std::shared_ptr<TBL>>, Status> get() {
        return FAIL;
    }
    sqljke::SelectQueryBuilder& select(const std::vector<std::variant<sqljke::Column, sqljke::Aggregate, sqljke::Scalar>> select_list);

    template <typename TBL>
    Status refresh() {
        return FAIL;
    }
    sqljke::UpdateQueryBuilder& update(const std::string& table_name);

    template <typename TBL>
    Status del() {
        return FAIL;
    }
    sqljke::DeleteQueryBuilder& delete_from(const sqljke::Table& table);

    

private:
    std::shared_ptr<IDriver> driver_;
    std::unique_ptr<sqljke::ISQLDialect> dialect_;

    sqljke::SelectQueryBuilder select_;
    sqljke::CreateTableQueryBuilder create_;
    sqljke::InsertQueryBuilder insert_;
    sqljke::UpdateQueryBuilder update_;
    sqljke::DeleteQueryBuilder delete_;

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

}}

#endif
