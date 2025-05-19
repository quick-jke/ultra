#include "sql_builder.hpp"

SQLBuilder::SQLBuilder(){
}


bool isDependency(std::set<OPTION> options){
    return (!options.count(OPTION::MANY_TO_MANY) && !options.count(OPTION::MANY_TO_ONE) && 
            !options.count(OPTION::ONE_TO_MANY) && !options.count(OPTION::ONE_TO_ONE));
}

std::string normalizeType(std::string type){
    return type;
}

std::optional<std::string> normalizeField(Field field){
    std::stringstream oss;
    if(isDependency(field.getOptions())){
        if(field.getOptions().count(OPTION::ID)){
            oss << "\t" << field.getName() << " INT PRIMARY KEY AUTO_INCREMENT";
        }else{
            oss << "\t" << field.getName() << " " << normalizeType(field.getType());
        }
        return oss.str();
    }else{
        return std::nullopt;
    }
    
    
}

std::vector<std::string> SQLBuilder::getSqlByEntities(std::set<Table> tables){
    std::vector<std::string> everything;
    std::vector<std::string> pure_tables;
    std::vector<std::string> many_to_many_tables;
    std::vector<std::string> foreign_keys;


    for(auto table : tables){
        std::stringstream pureoss;
        pureoss << "CREATE TABLE IF NOT EXISTS " << table.getName() << " (\n";
        for(auto field : table.getFields()){
            auto result = normalizeField(field);
            if (result.has_value()) {
                pureoss << result.value() << std::endl;
            }
        }

        pureoss << ");\n\n";
        pure_tables.push_back(pureoss.str());
    }

    for(auto pure : pure_tables){
        everything.push_back(pure);
    }

    return everything;

}
