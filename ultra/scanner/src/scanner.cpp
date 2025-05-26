#include "scanner.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <iterator>


namespace quick{
namespace ultra{
namespace fs = std::filesystem;

HeaderScanner::HeaderScanner(){}

bool isEntityFile(const fs::path& path) {
    return fs::is_regular_file(path) &&
           path.extension() == ".hpp" &&
           path.filename().string().find(".entity") != std::string::npos;
}

std::pair<OPTION, std::string> HeaderScanner::parseDependencyString(std::string dependency_string) {
    OPTION option = UNKNOWN;
    std::string table = "";
    size_t pos = -1;

    std::vector<std::string> posible_options = { "ONE_TO_ONE", "ONE_TO_MANY", "MANY_TO_MANY", "MANY_TO_ONE" };

    for (const auto& option_substr : posible_options) {
        if ((pos = dependency_string.find(option_substr)) != std::string::npos) {
            option = stringToOptionString(option_substr);

            size_t openPos = dependency_string.find('(');
            size_t closePos = dependency_string.find(')');

            if (openPos != std::string::npos && closePos != std::string::npos && openPos < closePos) {
                table = dependency_string.substr(openPos + 1, closePos - openPos - 1);
            }

            break;
        }
    }

    if (option == UNKNOWN || table.empty()) {
        throw std::runtime_error("Invalid dependency format or unknown option");
    }

    return { option, table };
}

std::vector<std::string> HeaderScanner::parseFieldTokens(std::string& field) {
    field.erase(std::remove(field.begin(), field.end(), ';'), field.end());
    std::istringstream iss(field);
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(tokens));
    return tokens;
}

std::pair<dependencies, std::set<Table>> HeaderScanner::parseDependenciesList(dependenciesByTables deps_by_tables) {
    dependencies dset{};
    std::set<Table> tablesSet;

    for (const auto& [table_name, fields] : deps_by_tables) {
        std::set<Field> tableFields;

        for (const auto& field : fields) {
            if (field.empty()) continue;

            bool isDependency = false;
            for (const auto& option_str : { "ONE_TO_ONE", "ONE_TO_MANY", "MANY_TO_MANY", "MANY_TO_ONE" }) {
                if (field.find(option_str) != std::string::npos) {
                    isDependency = true;
                    break;
                }
            }

            if (isDependency) {
                auto field_tokens = parseFieldTokens(const_cast<std::string&>(field));
                if (field_tokens.size() >= 1) {
                    try {
                        auto [option, table2] = parseDependencyString(field_tokens[0]);
                        tables ts{ table_name, table2 };
                        dset.insert({ option, ts });
                    }
                    catch (...) {
                        continue;
                    }
                }
            }
            else {
                std::string processedField = field;

                bool isId = (processedField.find("ID") != std::string::npos);
                if (isId) {
                    processedField.erase(processedField.begin(), processedField.begin() + 2);
                    processedField.erase(processedField.begin(),
                        std::find_if(processedField.begin(), processedField.end(),
                            [](char c) { return !std::isspace(c); }));
                }

                std::istringstream iss(processedField);
                std::vector<std::string> tokens;
                std::string token;

                while (iss >> token) {
                    tokens.push_back(token);
                }

                if (tokens.size() >= 2) {
                    std::string typeStr = tokens[0];
                    std::string nameStr = tokens[1];

                    nameStr.erase(std::remove(nameStr.begin(), nameStr.end(), ';'), nameStr.end());

                    SQLVAR sqlType = stringToSQLVAR(typeStr);

                    tableFields.emplace(nameStr, sqlType, isId);
                }
            }
        }

        tablesSet.emplace(table_name, tableFields);
    }

    return { dset, tablesSet };
}

std::pair<std::set<Table>, dependencies> HeaderScanner::getTablesAndDependencies(){
    dependenciesByTables deps_by_tables;
    try {
        for (const auto& entry : fs::recursive_directory_iterator("models")) {
            if (isEntityFile(entry.path())) {
                try {
                    auto [table_name, fields] = getTableStructure(entry.path().string());

                    deps_by_tables.insert({table_name, fields});

                } catch (const std::exception& e) {
                    std::cerr << "Error parsing file " << entry.path() << ": " << e.what() << "\n";
                }
            }
        }

        auto [dependencyList, tableStructs] = parseDependenciesList(deps_by_tables);

        return {tableStructs, dependencyList};
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return {std::set<Table>(), dependencies()};
    }
}

std::string trims(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\n\v\f\r");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\n\v\f\r");
    return s.substr(first, last - first + 1);
}

std::set<std::string> HeaderScanner::parseBody(const std::string& body){
    
    std::istringstream iss(body);
    std::string line;
    std::set<std::string> fields;

    while (std::getline(iss, line)) {
        line = trims(line);
        if (line.empty()) continue;
        
        fields.insert(line);
        
    }
    return fields;
}

std::pair<std::string, std::set<std::string>> HeaderScanner::getTableStructure(const std::string& filePath){

    fs::path path = fs::absolute(filePath);

    if (!fs::exists(path)) {
        throw std::runtime_error("File does not exist: " + path.string());
    }

    if (!fs::is_regular_file(path)) {
        throw std::runtime_error("Path is not a regular file: " + path.string());
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path.string());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    size_t entityPos = content.find("ENTITY ");
    if (entityPos == std::string::npos)
        throw std::runtime_error("No 'ENTITY' found in file");

    size_t nameStart = content.find_first_not_of(" \t\n\r", entityPos + 7);
    size_t nameEnd = content.find_first_of(" \t\n\r{", nameStart);

    std::string tableName = content.substr(nameStart, nameEnd - nameStart);

    size_t bodyStart = content.find("{", nameEnd);
    size_t bodyEnd = content.find("};", bodyStart);

    std::string tableBody = content.substr(bodyStart + 1, bodyEnd - bodyStart - 1);

    

    auto bodyFields = parseBody(tableBody);



    return { tableName, bodyFields };
}


}}