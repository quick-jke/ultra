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
#include "puretable.hpp"
#include "relation.hpp"
#define DEBUG
namespace quick {
namespace ultra {

class Session {
public:
    explicit Session(std::shared_ptr<IDriver> driver);

    template <typename TBL>
    std::shared_ptr<TBL> get(int id) {
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
    std::vector<std::shared_ptr<TBL>> get_all(std::vector<std::string> where = {}, int limit = -1, int offset = -1) {
        static_assert(std::is_base_of_v<quick::ultra::sqljke::SQLTable, TBL>, "Template argument must derive from SQLTable");

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
        static_assert(std::is_base_of_v<quick::ultra::sqljke::SQLTable, TBL>, "Template argument must derive from SQLTable");

        if (!obj) {
            std::cerr << "Error: null object passed to save()" << std::endl;
            return;
        }
        if(!is_exist(obj)){
            try {
                std::string sql = insert_
                                        .set_table(obj->table_name())
                                        .columns(obj->column_names())
                                        .values(obj->values())
                                        .build();

#ifdef DEBUG
                std::cout << "Executing SQL: " << sql << std::endl;
#endif
                execute(sql);
                int inserted_id = driver_->get_last_insert_id();
                obj->set_id(inserted_id);
            } catch (const std::exception& e) {
                std::cerr << "Exception during save(): " << e.what() << std::endl;
            }
        }else{
            std::cerr << "Object exist" << std::endl;
        }
        
    }
    
    template<typename TBL>
    bool is_exist(const std::shared_ptr<TBL>& obj){
        static_assert(std::is_base_of_v<quick::ultra::sqljke::SQLTable, TBL>, "Template argument must derive from SQLTable");
        try{
            auto squery = select({}).from(obj->table_name());
            for(size_t i = 0; i < obj->column_names().size(); ++i){

                squery.where(obj->column_names().at(i) + " = " 
                    + (obj->columns().at(i + 1).type == "string" ? "\'" : "") 
                    + obj->values().at(i)
                    + (obj->columns().at(i + 1).type == "string" ? "\'" : "")  
                );
            } 
            std::cout << squery.build() << std::endl;
            ResultSetPtr rs = driver_->query(squery.build());


            if (rs && rs->next()) {
                std::cout << "return true" << std::endl;
                return true;
            } else {
                std::cout << "return false" << std::endl;
                return false;
            }

        }catch (const std::exception& e) {
            std::cerr << "Exception during is_exist(): " << e.what() << std::endl;
        }
        return true;
    }
    

    sqljke::CreateTableQueryBuilder& create_table(const std::string& table_name);
    sqljke::SelectQueryBuilder& select(const std::vector<std::string>& columns);
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
};

}}// namespace quick::ultra

#endif
