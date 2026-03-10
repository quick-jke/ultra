#ifndef QUICK_ULTRA_SQL_INCLUDE_CREATE_TABLE_QUERY_IR_HPP
#define QUICK_ULTRA_SQL_INCLUDE_CREATE_TABLE_QUERY_IR_HPP
#include <string>
#include <vector>
#include "column.hpp"
#include "link.hpp"
namespace quick::ultra::sqljke{

struct TableDefinition {
    std::string name;
    std::vector<Column> columns;
    std::vector<Link> foreign_keys;
};
    
struct CreateTableIR{
    std::vector<TableDefinition> tables;
    bool if_not_exists_;
};
}

#endif
