#include "sql_builder.hpp"

namespace quick{
namespace ultra{


SQLBuilder::SQLBuilder(){
}


bool isDependency(std::set<OPTION> options){
    return (!options.count(OPTION::MANY_TO_MANY) && !options.count(OPTION::MANY_TO_ONE) && 
            !options.count(OPTION::ONE_TO_MANY) && !options.count(OPTION::ONE_TO_ONE));
}



std::optional<std::string> normalizeField(Field field){
    std::stringstream oss;
    if(isDependency(field.getOptions())){
        if(field.getOptions().count(OPTION::ID)){
            oss << "\t" << field.getName() << " INT PRIMARY KEY AUTO_INCREMENT";
        }else{
            oss << "\t" << field.getName() << " " << varToString(field.getType());
        }
        return oss.str();
    }else{
        return std::nullopt;
    }
    
    
}

std::vector<std::string> SQLBuilder::getSqlByEntities(std::set<Table> tables) {
    std::vector<std::string> everything;
    
    for (const auto& table : tables) {
        std::stringstream createStmt;
        createStmt << "CREATE TABLE IF NOT EXISTS `" << table.getName() << "` (\n";

        std::vector<std::string> fieldsSQL;

        for (const auto& field : table.getFields()) {
            auto fieldDef = normalizeField(field);
            if (fieldDef.has_value()) {
                fieldsSQL.push_back(fieldDef.value());
            }
        }

        if (fieldsSQL.empty()) {
            continue; // Пропустим пустые таблицы
        }

        // Добавляем поля с запятыми
        for (size_t i = 0; i < fieldsSQL.size(); ++i) {
            createStmt << fieldsSQL[i];
            if (i != fieldsSQL.size() - 1) {
                createStmt << ",";
            }
            createStmt << "\n";
        }

        createStmt << ");\n\n";
        everything.push_back(createStmt.str());
    }

    return everything;
}
    
}
}