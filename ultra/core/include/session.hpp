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
namespace quick {
namespace ultra {

class Session {
public:
    explicit Session(std::shared_ptr<IDriver> driver);

    void create_tables(std::vector<sqljke::PureTable> tables);
    ResultSetPtr select(sqljke::SelectQuery query);
    
    //future
    bool is_exist(std::shared_ptr<sqljke::SQLTable> table);
    void insert_into(std::shared_ptr<sqljke::SQLTable> table);
    //future
    void create_table();
    void update();
    void delete_from();
    void drop_table();
    void table_exists();
    void truncate_table();
    

private:
    std::shared_ptr<IDriver> driver_;
    std::unique_ptr<sqljke::ISQLDialect> dialect_;
};

}}// namespace quick::ultra

#endif
