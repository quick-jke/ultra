#ifndef SQL_BUILDER_HPP
#define SQL_BUILDER_HPP

#include <iostream>
#include "table.hpp"
#include "sql.hpp"
#include <set>

#include <map>
#include <queue>
#include <sstream>
#include <optional>

class SQLBuilder{
public:
    SQLBuilder();

    std::string createTables(std::set<Table> tables);


private:
    std::optional<std::string> getNormalizeField(Field field, const std::string& tableName);
    std::set<std::string> foreign_keys_;
};

#endif