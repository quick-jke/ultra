#ifndef QUICK_ULTRA_SQL_INCLUDE_SELECT_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_SELECT_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include "table.hpp"
#include "order_dir.hpp"
#include "aggregate.hpp"
#include "scalar.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <variant>
namespace quick::ultra::sqljke {
struct SelectQuery{
    std::vector<std::string> columns;
    std::string table_name;
    std::string where;
    std::variant<int, std::pair<int, int>> limit;
};

class SelectQueryBuilder : public SQLQueryBuilder {
public:
    SelectQueryBuilder(const ISQLDialect* dialect);

    void set_columns(const std::vector<Column>& columns);

    void set_aggregate(const Aggregate aggregate);

    void set_select_list(const std::vector<std::variant<Column, Aggregate, Scalar>> select_list);

    SelectQueryBuilder& from(Table table);

    SelectQueryBuilder& where(Expression expression);

    SelectQueryBuilder& group_by(const std::vector<Column>& columns); 

    SelectQueryBuilder& having(Expression expression);

    SelectQueryBuilder& order_by(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs); 

    SelectQueryBuilder& limit(int limit, int offset = 0);

    std::string build();


private:
    const ISQLDialect* dialect_;
    std::vector<Column> columns_;
    std::vector<std::variant<Column, Aggregate, Scalar>> select_list_;
    std::string table_name_;
    std::vector<std::string> where_clauses_;
    int limit_ = -1;
    int offset_ = 0;
    std::string having_clause_;
    std::string group_by_clause_;
    std::string order_by_clause_;
    bool is_aggregate_ = false;
    Aggregate aggregate_;
};
}// namespace quick::ultra::sql
#endif

