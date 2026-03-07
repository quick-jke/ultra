#ifndef QUICK_ULTRA_SQL_INCLUDE_UPDATE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_UPDATE_QUERY_BUILDER_HPP
#include <map>
#include <string>
#include "utility"
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include <sstream>
#include "update_query_ir.hpp"

namespace quick::ultra::sqljke{

class UpdateQueryBuilder : public SQLQueryBuilder{
public:
    explicit UpdateQueryBuilder(const ISQLDialect* dialect) : dialect_(dialect), table_(nullptr){}

    UpdateQueryBuilder& set_table(const Table& table);

    UpdateQueryBuilder& set(const std::vector<Column>& columns, const std::vector<std::string>& values);
    
    UpdateQueryBuilder& set(const Column& column, const std::string& value);
    
    UpdateQueryBuilder& where(const Expression& expression);

    std::string build() const;

    void reset();

private:
    const ISQLDialect* dialect_;
    const Table* table_; 
    std::map<const Column*, std::string> column_value_map_; 
    std::vector<Expression> where_clauses_; 
};


}


#endif
