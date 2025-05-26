#ifndef SQL_BUILDER_HPP
#define SQL_BUILDER_HPP

#include <iostream>
#include "dep.hpp"
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
    std::string sqlCreateDependency(dependency dep);

    std::vector<std::string> getSqlByEntitiesAndDependencies(std::set<Table> tables, dependencies dep_set);


private:
    std::optional<std::string> normalizeField(const std::string& tableName, Field field);
    std::vector<std::string> foreign_keys_;

};

}}

#endif