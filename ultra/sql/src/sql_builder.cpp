#include "sql_builder.hpp"
#include <numeric>

namespace quick{
namespace ultra{

SQLBuilder::SQLBuilder(){}

std::optional<std::string> SQLBuilder::normalizeField(const std::string& tableName, Field field){
    std::stringstream oss;
    if(field.isIdentity()){
        oss << "\t" << field.getName() << " INT PRIMARY KEY AUTO_INCREMENT";
    }else{
        oss << "\t" << field.getName() << " " << varToString(field.getType());
    }
    return oss.str();
}

std::string SQLBuilder::sqlCreateTable(Table table){
    std::stringstream createStmt;
    createStmt << "CREATE TABLE IF NOT EXISTS `" << table.getName() << "` (\n";
    std::vector<std::string> fieldsSQL;
    for (const auto& field : table.getFields()) {
        auto fieldDef = normalizeField(table.getName(), field);
        if (fieldDef.has_value()) {
            fieldsSQL.push_back(fieldDef.value());
        }
    }
    for (size_t i = 0; i < fieldsSQL.size(); ++i) {
        createStmt << fieldsSQL[i];
        if (i != fieldsSQL.size() - 1) {
            createStmt << ",";
        }
        createStmt << "\n";
    }

    createStmt << ");\n\n";

    return createStmt.str();

}

std::string SQLBuilder::sqlCreateDependency(dependency dep){
    std::stringstream oss;
    auto [tab1, tab2] = dep.second;
    switch (dep.first)
    {
    case ONE_TO_ONE: {
        oss << "ALTER TABLE " << tab1 << std::endl;
        oss << "ADD COLUMN " << tab2 << "_id INT," << std::endl;
        oss << "ADD FOREIGN KEY (" << tab2 << "_id) REFERENCES " << tab2 << "(id);" << std::endl << std::endl;
        break;
    }

    case ONE_TO_MANY: {
        oss << "ALTER TABLE " << tab2 << std::endl;
        oss << "ADD COLUMN " << tab1 << "_id INT," << std::endl;
        oss << "ADD FOREIGN KEY (" << tab1 << "_id) REFERENCES " << tab1 << "(id);" << std::endl << std::endl;
        
        break;
    }
    case MANY_TO_ONE: {
        oss << "ALTER TABLE " << tab1 << std::endl;
        oss << "ADD COLUMN " << tab2 << "_id INT," << std::endl;
        oss << "ADD FOREIGN KEY (" << tab2 << "_id) REFERENCES " << tab2 << "(id);" << std::endl << std::endl;
        break;
    }
    case MANY_TO_MANY: {
        oss << "CREATE TABLE " << tab1 << "_" << tab2 << "(" << std::endl;
        oss << "\t" << tab1 << "_id INT," << std::endl;
        oss << "\t" << tab2 << "_id INT," << std::endl;
        oss << "\t" << "FOREIGN KEY (" << tab1 << "_id)" << "REFERENCES " << tab1 << "(id)," << std::endl;
        oss << "\t" << "FOREIGN KEY (" << tab2 << "_id)" << "REFERENCES " << tab2 << "(id)," << std::endl;
        oss << "\t" << "PRIMARY KEY (" << tab1 << "_id, " << tab2 << "_id)" << std::endl;
        oss << ");" << std::endl;
        break;
    }
    default:
        break;
    }
    return oss.str();
}
    

std::string joinWithComma(const std::vector<std::string>& vec, bool add_quotes = false) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        if (add_quotes) {
            oss << "'" << vec[i] << "'";
        } else {
            oss << vec[i];
        }
    }
    return oss.str();
}

std::string SQLBuilder::INSERT(const std::string& tableName, std::vector<std::string> fields, std::vector<std::string> values ){
    return "INSERT INTO " + tableName + " (" + joinWithComma(fields) + ") VALUES (" + joinWithComma(values, true) + ");";
}


}
}