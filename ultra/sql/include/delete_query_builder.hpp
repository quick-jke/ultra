#ifndef QUICK_ULTRA_SQL_INCLUDE_DELETE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_DELETE_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"

namespace quick::ultra::sqljke {

class DeleteQueryBuilder : public SQLQueryBuilder {
public:
    explicit DeleteQueryBuilder(const ISQLDialect* dialect) : dialect_(dialect) {}

    DeleteQueryBuilder& set_table(Table table);

    DeleteQueryBuilder& where(const Expression& expression);

    std::string build();

private:
    const ISQLDialect* dialect_;
    std::string table_name_;
    std::vector<std::string> where_clauses_;

};

}

#endif
