#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP
#include "idriver.hpp"
#include <iostream>
#include "mysql_dialect.hpp"
#include "create_table_query_builder.hpp" 
#include "select_query_builder.hpp"
#include "insert_query_builder.hpp"
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

    
    //select
    sqljke::SelectQueryBuilder& select(const std::vector<std::string>& columns);
    template <typename TBL>
    std::shared_ptr<TBL> get(int id) {
        static_assert(std::is_base_of_v<quick::ultra::sqljke::SQLTable, TBL>,
                    "Template argument must derive from SQLTable");

        auto select = std::make_unique<sqljke::SelectQueryBuilder>(dialect_.get());

        std::string sql = select->from(TBL().table_name())
                                .where("id = " + std::to_string(id))
                                .build();

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

    //create
    sqljke::CreateTableQueryBuilder& create_table(const std::string& table_name);
    void create_tables(std::vector<std::shared_ptr<sqljke::SQLTable>> tables);

    //insert
    sqljke::InsertQueryBuilder& insert_into(const std::string& table_name);
    void save(std::shared_ptr<sqljke::SQLTable> table);
    
    bool is_exist(std::shared_ptr<sqljke::SQLTable> table);

    ResultSetPtr execute(const std::string& sql);


    //future
    void create_table();
    void update();
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
};

}}// namespace quick::ultra

#endif
