#ifndef QUICK_ULTRA_SQL_INCLUDE_INSERT_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_INSERT_QUERY_BUILDER_HPP

#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include <string>
#include <sstream>
#include <vector>

namespace quick::ultra::sqljke {

class InsertQueryBuilder : public SQLQueryBuilder {
public:
    explicit InsertQueryBuilder(const ISQLDialect* dialect) : dialect_(dialect){}

    InsertQueryBuilder& set_table(const std::string& table_name);

    InsertQueryBuilder& columns(const std::vector<std::string>& columns);

    InsertQueryBuilder& values(const std::vector<std::string>& values);

    std::string build() const;

private:
    const ISQLDialect* dialect_;
    std::string table_name_;
    std::vector<std::string> columns_;
    std::vector<std::string> values_;

    bool is_string_value(const std::string& val) const;
};

}

#endif
