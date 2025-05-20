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


namespace quick{
namespace ultra{

class HeaderScanner {
public:
    std::optional<std::set<Table>> getTables();
private:
    bool isEntityFile(const std::filesystem::path& path);
    Table getTableFromFile(const std::string& filePath);
    std::pair<std::set<Field>, std::set<std::string>> getFieldsByBody(const std::string& body); 
};
}}

#endif 