#ifndef SQL_BUILDER_HPP
#define SQL_BUILDER_HPP

#include <iostream>
#include "table.hpp"
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <optional>

#include <memory>

namespace quick{
namespace ultra{

class SQLBuilder{
public:
    SQLBuilder();
    
    std::string sqlCreateTable(Table table);
    std::vector<std::string> getSqlByEntities(std::set<Table> tables);


private:

    std::vector<std::string> sqls_;
};

}}

#endif