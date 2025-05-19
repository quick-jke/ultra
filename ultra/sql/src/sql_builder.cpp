#include "sql_builder.hpp"

SQLBuilder::SQLBuilder(){
}




std::string getReferencedTableName(const std::string& type) {
    std::string result = type;

    size_t template_open = result.find('<');
    if (template_open != std::string::npos) {
        size_t template_close = result.rfind('>');
        if (template_close != std::string::npos && template_close > template_open) {
            result = result.substr(template_open + 1, template_close - template_open - 1);
        }
    }

    while (!result.empty() && (result.back() == '*' || result.back() == ' ')) {
        result.pop_back();
    }

    return result;
}

std::string generateManyToManyTables(std::set<Table> tables) {
    std::ostringstream oss;
    std::set<std::pair<std::string, std::string>> processed;

    for (auto table : tables) {
        for (auto field : table.getFields()) {
            if (field.getOptions().count(OPTION::MANY_TO_MANY)) {
                std::string other_table = getReferencedTableName(field.getType());
                std::string table1 = table.getName();
                std::string table2 = other_table;

                if (table1 > table2) std::swap(table1, table2);

                if (processed.count({table1, table2})) {
                    continue;
                }

                processed.insert({table1, table2});

                std::string join_table = table1 + "_" + table2;

                oss << "CREATE TABLE IF NOT EXISTS " << join_table << " (" << std::endl;
                oss << "\t" << table1 << "_id INT REFERENCES " << table1 << "(id)," << std::endl;
                oss << "\t" << table2 << "_id INT REFERENCES " << table2 << "(id)," << std::endl;
                oss << "\tPRIMARY KEY (" << table1 << "_id, " << table2 << "_id)" << std::endl;
                oss << ");\n" << std::endl;
            }
        }
    }

    return oss.str();
}


std::optional<std::string> SQLBuilder::getNormalizeField(Field field, const std::string& tableName) {
    std::string sql_type;
    std::string referenced_table = getReferencedTableName(field.getType());
    

    if(!field.getOptions().count(OPTION::MANY_TO_MANY) && !field.getOptions().count(OPTION::MANY_TO_ONE) && 
        !field.getOptions().count(OPTION::ONE_TO_MANY) && !field.getOptions().count(OPTION::ONE_TO_ONE)){

        if(field.getOptions().count(OPTION::ID)){
            return "\t" + field.getName() + " INT PRIMARY KEY AUTO_INCREMENT";
        }else{
            if (field.getType() == "int") {
                sql_type = " INT";
            } else if (field.getType() == "std::string" || field.getType() == "string") {
                sql_type = " VARCHAR(255)";
            }
            return "\t" + field.getName() + sql_type;
        }
    }else if(!field.getOptions().count(OPTION::MANY_TO_MANY) && !field.getOptions().count(OPTION::ONE_TO_MANY)){
        foreign_keys_.insert(
            "ALTER TABLE " + tableName + 
            "\nADD COLUMN " + referenced_table + "_id INTEGER REFERENCES " + referenced_table + "(id);"
        ); 
    }
    return std::nullopt;
}

std::string generateForeignKeys(std::set<std::string> keys){
    std::ostringstream oss;
    for(auto str : keys){
        oss << str << std::endl << std::endl;
    }

    return oss.str();
}


std::string SQLBuilder::createTables(std::set<Table> tables) {
    std::ostringstream oss;
    for (const auto& table : tables) {
        
        oss << "CREATE TABLE IF NOT EXISTS " << table.getName() << " (\n";

        std::vector<std::string> fieldLines;

        for (const auto& field : table.getFields()) {
            auto line = getNormalizeField(field, table.getName());
            if (line.has_value()) {
                fieldLines.push_back(line.value());
            }
        }

        if (!fieldLines.empty()) {
            for (size_t i = 0; i < fieldLines.size(); ++i) {
                oss << fieldLines[i];
                if (i != fieldLines.size() - 1) {
                    oss << ",";
                }
                oss << "\n";
            }
        }

        oss << ");\n\n";
        
    }

    oss << generateManyToManyTables(tables);
    oss << generateForeignKeys(foreign_keys_);
    std::cout << oss.str();
    return oss.str();
}
