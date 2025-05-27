#ifndef SQL_BUILDER_HPP
#define SQL_BUILDER_HPP

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <optional>
#include <memory>
#include <vector>

#include "dep.hpp"
#include "table.hpp"

namespace quick{
namespace ultra{

class SQLBuilder{
public:
    SQLBuilder();
    
    std::string sqlCreateTable(Table table);
    std::string sqlCreateDependency(dependency dep);

    static std::string INSERT(const std::string& tableName, std::vector<std::string> fields, std::vector<std::string> values );

private:
    std::optional<std::string> normalizeField(const std::string& tableName, Field field);
    std::vector<std::string> foreign_keys_;


};

}}

#endif