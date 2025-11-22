#ifndef QUICK_ULTRA_SQL_INCLUDE_BUILDER_FACTORY_HPP
#define QUICK_ULTRA_SQL_INCLUDE_BUILDER_FACTORY_HPP
#include "sql_query_builder.hpp"
#include "select_query_builder.hpp"
#include "create_table_query_builder.hpp"
#include <string>
#include <sstream>
#include <memory>
namespace quick{
namespace ultra{
namespace sqljke {
class SQLBuilderFactory {
public:
    static std::unique_ptr<SQLQueryBuilder> createSelectBuilder(const ISQLDialect* dialect) {
        return std::make_unique<SelectQueryBuilder>(dialect);
    }

    static std::unique_ptr<SQLQueryBuilder> createCreateTableBuilder(const ISQLDialect* dialect, const std::string& table_name) {
        return std::make_unique<CreateTableQueryBuilder>(dialect, table_name);
    }
};
}}}// namespace quick::ultra::sql
#endif
