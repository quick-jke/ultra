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

class SQLBuilder{
public:
    SQLBuilder();

    std::string createTables(std::set<Table> tables);


   
    //
    
    std::string sqlCreateTable(Table table);
    std::vector<std::string> getSqlByEntities(std::set<Table> tables);


private:
    std::optional<std::string> getNormalizeField(Field field, const std::string& tableName);
    std::set<std::string> foreign_keys_;

    //

    std::vector<std::string> sqls_;
};

#endif