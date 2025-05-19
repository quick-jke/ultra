#include "scanner.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;



bool HeaderScanner::isEntityFile(const fs::path& path) {
    return fs::is_regular_file(path) &&
           path.extension() == ".hpp" &&
           path.filename().string().find(".entity") != std::string::npos;
}

std::optional<std::set<Table>> HeaderScanner::getTables(){
    std::set<Table> tables;
    try {
        for (const auto& entry : fs::recursive_directory_iterator("models")) {
            if (isEntityFile(entry.path())) {
                try {
                    tables.insert(getTableFromFile(entry.path().string()));
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing file " << entry.path() << ": " << e.what() << "\n";
                }
            }
        }
        return tables;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return std::nullopt;
    }
}

Table HeaderScanner::getTableFromFile(const std::string& filePath){
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

    size_t structPos = content.find("struct ");
    if (structPos == std::string::npos)
        throw std::runtime_error("No 'struct' found in file");

    size_t nameStart = content.find_first_not_of(" \t\n\r", structPos + 7);
    size_t nameEnd = content.find_first_of(" \t\n\r{", nameStart);

    std::string tableName = content.substr(nameStart, nameEnd - nameStart);

    size_t bodyStart = content.find("{", nameEnd);
    size_t bodyEnd = content.find("};", bodyStart);

    std::string tableBody = content.substr(bodyStart + 1, bodyEnd - bodyStart - 1);

    // std::cout << "name: " << tableName << std::endl << "body: " << tableBody << std::endl;

    auto [fields, dependencies] = getFieldsByBody(tableBody);


    return Table(tableName, fields, dependencies);
}

std::string trims(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\n\v\f\r");
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(" \t\n\v\f\r");
    return s.substr(first, last - first + 1);
}
bool isOptionKeyword(const std::string& line, std::set<OPTION>& pendingOptions) {
    if (line == "ID") {
        pendingOptions.insert(OPTION::ID);
        return true;
    } else if (line == "MANY_TO_MANY") {
        pendingOptions.insert(OPTION::MANY_TO_MANY);
        return true;
    } else if (line == "ONE_TO_MANY") {
        pendingOptions.insert(OPTION::ONE_TO_MANY);
        return true;
    } else if (line == "MANY_TO_ONE") {
        pendingOptions.insert(OPTION::MANY_TO_ONE);
        return true;
    } else if (line == "ONE_TO_ONE") {
        pendingOptions.insert(OPTION::ONE_TO_ONE);
        return true;
    }
    return false;
}
void parseFieldLine(const std::string& line, std::string& type, std::string& name) {
    size_t lastSpace = line.find_last_of(' ');
    if (lastSpace == std::string::npos || lastSpace == 0) {
        type = "";
        name = "";
        return;
    }
    name = line.substr(lastSpace + 1);
    if(!name.empty()){
        name.pop_back();
    }
    type = line.substr(0, lastSpace);
}

bool isPrimitiveType(const std::string& type) {
    return type == "int" || type == "std::string";
}
void extractDependenciesFromType(const std::string& typeStr, std::set<std::string>& dependencies) {
    std::string baseType = typeStr;
    bool isVector = false;

    if (baseType.find("std::vector<") != std::string::npos) {
        isVector = true;
        size_t start = baseType.find('<');
        size_t end = baseType.rfind('>');
        if (start != std::string::npos && end != std::string::npos && end > start + 1) {
            baseType = baseType.substr(start + 1, end - start - 1);
            baseType = trims(baseType);
        } else {
            return; 
        }
    }

    if (!baseType.empty() && baseType.back() == '*') {
        baseType.pop_back();
        baseType = trims(baseType);
    }

    if (!isPrimitiveType(baseType) && !baseType.empty()) {
        dependencies.insert(baseType);
    }
}

std::pair<std::set<Field>, std::set<std::string>> HeaderScanner::getFieldsByBody(const std::string& body) {
    std::set<Field> fields;
    std::set<std::string> dependencies;
    std::istringstream iss(body);
    std::string line;
    std::set<OPTION> pendingOptions;

    while (std::getline(iss, line)) {
        line = trims(line);
        if (line.empty()) continue;

        if (isOptionKeyword(line, pendingOptions)) {
            continue;
        }

        std::string fieldTypeStr, fieldName;
        parseFieldLine(line, fieldTypeStr, fieldName);

        if (fieldName.empty() || fieldTypeStr.empty()) {
            continue; 
        }

        extractDependenciesFromType(fieldTypeStr, dependencies);

        fields.insert({fieldName, fieldTypeStr, pendingOptions});
        pendingOptions.clear();
    }

    

    return {fields, dependencies};
}