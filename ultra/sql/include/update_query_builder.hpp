#ifndef QUICK_ULTRA_SQL_INCLUDE_UPDATE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_UPDATE_QUERY_BUILDER_HPP
#include <map>
#include <string>
#include "utility"
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include <sstream>

namespace quick::ultra::sqljke{

class UpdateQueryBuilder : public SQLQueryBuilder{
public:
    explicit UpdateQueryBuilder(const ISQLDialect* dialect) : dialect_(dialect){}

    UpdateQueryBuilder& set_table(const Table& table);

    UpdateQueryBuilder& set(const std::vector<std::string>& columns, const std::vector<std::string>& values);
    
    UpdateQueryBuilder& set(const std::string& column, const std::string& value);

    UpdateQueryBuilder& add_column_value(std::pair<std::string, std::string> pair);
    
    UpdateQueryBuilder& where(const Expression& expression);

    std::string build() const;

private:
    const ISQLDialect* dialect_;
    std::string table_name_;
    std::map<std::string, std::string> column_value_map_;
    std::vector<std::string> where_clauses_;
};


}


#endif
