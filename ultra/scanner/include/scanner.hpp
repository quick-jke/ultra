#ifndef QUICK_ULTRA_SCANNER_HPP
#define QUICK_ULTRA_SCANNER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <set>
#include <optional>
#include <memory>

#include "table.hpp"
#include "dep.hpp"


namespace quick{
namespace ultra{

class HeaderScanner {
public:
    HeaderScanner();
    std::pair<std::set<Table>, dependencies> getTablesAndDependencies();
    
private:
    std::pair<OPTION, std::string> parseDependencyString(std::string dependency_string);
    std::vector<std::string> parseFieldTokens(std::string& field);
    std::pair<dependencies, std::set<Table>> parseDependenciesList(dependenciesByTables deps_by_tables);
    std::set<std::string> parseBody(const std::string& body);
    std::pair<std::string, std::set<std::string>> getTableStructure(const std::string& filePath);

};
}}

#endif 