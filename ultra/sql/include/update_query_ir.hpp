#ifndef QUICK_ULTRA_SQL_INCLUDE_UPDATE_QUERY_IR_HPP
#define QUICK_ULTRA_SQL_INCLUDE_UPDATE_QUERY_IR_HPP
#include "table.hpp"
#include "column.hpp"
#include "expr.hpp"

#include <map>
namespace quick::ultra::sqljke{
struct UpdateQueryIR {
    const Table* table = nullptr;
    std::map<const Column*, std::variant<std::string, int, double, bool>> column_value_map;
    std::vector<Expression> where_clauses;
    UpdateQueryIR(){reset();}
    void reset() {
        table = nullptr; 
        column_value_map.clear(); 
        where_clauses.clear(); 
    }
};
}

#endif
