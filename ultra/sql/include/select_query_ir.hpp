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
    const Table* table = nullptr;
    std::vector<Expression> where_clauses;  
    
    std::optional<std::vector<Column>> group_by_columns;
    std::optional<std::vector<std::pair<Column, ORDER_DIR>>> order_by_columns;
    
    std::optional<std::pair<int, int>> limit_offset; 
    std::optional<Expression> having_clause;  
};
}
#endif
