#ifndef ULTRA_SQL_INCLUDE_SELECT_QUERY_IR_HPP
#define ULTRA_SQL_INCLUDE_SELECT_QUERY_IR_HPP
#include <string>
#include <vector>
#include <optional>
#include <variant>

#include "column.hpp"
#include "aggregate.hpp"
#include "scalar.hpp"
namespace quick::ultra::sqljke{

struct SelectQueryIR {
    std::vector<std::variant<Column, Aggregate, Scalar>> select_list;
    std::string table_name; 
    std::vector<std::string> where_clauses;
    std::string group_by_columns;
    std::string order_by_columns;
    std::optional<std::pair<int, int>> limit_offset; 
    std::optional<std::string> having_clause;
};
}
#endif
