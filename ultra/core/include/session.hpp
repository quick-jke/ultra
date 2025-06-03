#ifndef CORE_SESSION_HPP
#define CORE_SESSION_HPP
#include "idriver.hpp"
#include <iostream>
#include "mysql_dialect.hpp"
#include "create_table_query_builder.hpp" 
#include "select_query_builder.hpp"
#include "sql_dialect.hpp"
#include "mysql_result_set.hpp"
namespace quick {
namespace ultra {
class Session {
public:
    explicit Session(std::shared_ptr<IDriver> driver);

    void create_tables();
    void select();

private:
    std::shared_ptr<IDriver> driver_;
    std::unique_ptr<ISQLDialect> dialect_;
};

}}// namespace quick::ultra

#endif