#include "scanner.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace quick{
namespace ultra{

namespace fs = std::filesystem;


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
void parseFieldLine(const std::string& line, SQLVAR& type, std::string& name) {
    std::string trimmed = trims(line);
    if (trimmed.empty()) {
        type = SQLVAR::OBJECT;
        name = "";
        return;
    }

    // Извлекаем имя поля
    size_t nameStart = trimmed.find_last_of(' ');
    if (nameStart == std::string::npos || nameStart == 0) {
        name = "";
        type = SQLVAR::OBJECT;
        return;
    }

    name = trimmed.substr(nameStart + 1);
    if (!name.empty() && name.back() == ';') name.pop_back();
    name = trims(name);

    // Извлекаем тип
    std::string typeStr = trimmed.substr(0, nameStart);
    typeStr = trims(typeStr);

    if (typeStr.find("ONE_TO_ONE") != std::string::npos) {
        type = SQLVAR::OBJECT;
    } else if (typeStr.find("ONE_TO_MANY") != std::string::npos ||
               typeStr.find("MANY_TO_MANY") != std::string::npos) {
        type = SQLVAR::VECTOR;
    } else if (typeStr.find("MANY_TO_ONE") != std::string::npos) {
        type = SQLVAR::OBJECT;
    } else {
        type = stringToSQLVAR(typeStr);
    }
}
bool isPrimitiveType(const std::string& type) {
    return type == "int" || type == "std::string" || type == "long" || type == "double";
}

void extractDependenciesFromType(const std::string& typeStr, std::set<std::string>& dependencies) {
    std::string baseType;

    if (typeStr.find("ONE_TO_ONE") != std::string::npos ||
        typeStr.find("MANY_TO_ONE") != std::string::npos) {

        size_t start = typeStr.find('(');
        size_t end = typeStr.find(')');
        if (start != std::string::npos && end != std::string::npos && end > start + 1) {
            baseType = typeStr.substr(start + 1, end - start - 1);
            baseType = trims(baseType);
            if (!isPrimitiveType(baseType) && !baseType.empty()) {
                dependencies.insert(baseType);
            }
        }

    } else if (typeStr.find("ONE_TO_MANY") != std::string::npos ||
               typeStr.find("MANY_TO_MANY") != std::string::npos) {

        size_t start = typeStr.find('(');
        size_t end = typeStr.find(')');
        if (start != std::string::npos && end != std::string::npos && end > start + 1) {
            baseType = typeStr.substr(start + 1, end - start - 1);
            baseType = trims(baseType);
            if (!isPrimitiveType(baseType) && !baseType.empty()) {
                dependencies.insert(baseType);
            }
        }
    }
}

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
                    Table table = getTableFromFile(entry.path().string());
                    tables.insert(table);
                    // std::cout << table.toString() << std::endl;
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

    size_t entityPos = content.find("ENTITY ");
    if (entityPos == std::string::npos)
        throw std::runtime_error("No 'ENTITY' found in file");

    size_t nameStart = content.find_first_not_of(" \t\n\r", entityPos + 7);
    size_t nameEnd = content.find_first_of(" \t\n\r{", nameStart);

    std::string tableName = content.substr(nameStart, nameEnd - nameStart);

    size_t bodyStart = content.find("{", nameEnd);
    size_t bodyEnd = content.find("};", bodyStart);

    std::string tableBody = content.substr(bodyStart + 1, bodyEnd - bodyStart - 1);
    
    auto fields = getFieldsByBody(tableBody);

    return Table(tableName, fields);
}

Field parseField(const std::string& line) {
    std::set<OPTION> options;
    std::string processedLine = trims(line);

    // Шаг 1: Извлечение опций (ID, ONE_TO_MANY и т.д.)
    std::istringstream iss(processedLine);
    std::string token;

    while (iss >> token) {
        if (!isOptionKeyword(token, options)) {
            // Возвращаем поток на шаг назад
            std::istringstream rest((token + " " + std::string(std::istreambuf_iterator<char>(iss), {})));
            processedLine = rest.str();
            break;
        }
    }

    // Шаг 2: Извлечение типа и имени
    std::string typeName, fieldName;

    // Проверка на макросы вроде ONE_TO_MANY(Product) field;
    size_t macroStart = processedLine.find('(');
    size_t macroEnd = processedLine.find(')');
    if (macroStart != std::string::npos && macroEnd != std::string::npos) {
        std::string macroType = processedLine.substr(0, macroStart);
        std::string innerType = processedLine.substr(macroStart + 1, macroEnd - macroStart - 1);
        fieldName = processedLine.substr(macroEnd + 1);
        
        // Очистка имени
        fieldName = trims(fieldName);
        if (fieldName.back() == ';') fieldName.pop_back();
        fieldName = trims(fieldName);

        // Определение SQLVAR
        if (macroType == "ONE_TO_MANY" || macroType == "MANY_TO_MANY") {
            typeName = "std::vector<" + trims(innerType) + ">";
        } else {
            typeName = trims(innerType);
        }
    } else {
        // Обычный случай: int id; или std::string name;
        size_t lastSpace = processedLine.find_last_of(' ');
        if (lastSpace == std::string::npos) {
            throw std::runtime_error("Invalid field declaration");
        }

        fieldName = processedLine.substr(lastSpace + 1);
        if (fieldName.back() == ';') fieldName.pop_back();
        fieldName = trims(fieldName);

        typeName = processedLine.substr(0, lastSpace);
    }

    // Шаг 3: Определение SQLVAR на основе typeName
    SQLVAR sqlType = SQLVAR::OBJECT;
    if (typeName == "int") {
        sqlType = SQLVAR::INT;
    } else if (typeName == "std::string") {
        sqlType = SQLVAR::STRING;
    } else if (typeName.find("std::vector<") != std::string::npos) {
        sqlType = SQLVAR::VECTOR;
    }
    Field field(fieldName, sqlType, options);
    std::cout << field.toString() << std::endl;
    return field;
}

std::set<Field> HeaderScanner::getFieldsByBody(const std::string& body) {
    std::set<Field> fields;
    std::istringstream iss(body);
    std::string line;

    while (std::getline(iss, line)) {
        line = trims(line);
        if (line.empty()) continue;

        fields.emplace(parseField(line));
    }

    return fields;
}

}}