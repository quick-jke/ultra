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
    std::set<Field> getFieldsByBody(const std::string& body); 
};
}}

#endif 