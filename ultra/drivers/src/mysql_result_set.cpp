#include "mysql_result_set.hpp"
#include <cppconn/metadata.h>
namespace quick {
namespace ultra {
MySQLResultSet::MySQLResultSet(sql::ResultSet* rs)
    : result_set_(rs) {}

MySQLResultSet::~MySQLResultSet() = default;

bool MySQLResultSet::next() {
    return result_set_->next();
}

int MySQLResultSet::get_int(const std::string& column) {
    return result_set_->getInt(column);
}

std::string MySQLResultSet::get_string(const std::string& column) {
    return result_set_->getString(column).c_str(); 
}

bool MySQLResultSet::get_bool(const std::string& column) {
    return result_set_->getBoolean(column); 
}

double MySQLResultSet::get_double(const std::string& column) {
    return result_set_->getDouble(column); 
}
char MySQLResultSet::get_char(const std::string& column) {
    return result_set_->getString(column)[0]; 
}
std::string MySQLResultSet::debug() {
    if (!result_set_) {
        return "[empty result set]\n";
    }

    std::stringstream oss;
    
    sql::ResultSetMetaData* meta = result_set_->getMetaData();
    int col_count = meta->getColumnCount();

    oss << "Result set (" << col_count << " column" << (col_count != 1 ? "s" : "") << "):\n";
    oss << "Headers: ";
    for (int i = 1; i <= col_count; ++i) {  
        if (i > 1) oss << ", ";
        oss << "'" << meta->getColumnName(i) << "'";
    }
    oss << "\n";
    oss << "--------\n";

    int row_num = 0;
    while (result_set_->next()) {
        row_num++;
        oss << "Row " << row_num << ":\n";
        for (int i = 1; i <= col_count; ++i) {
            std::string col_name = meta->getColumnLabel(i);
            try {
                std::string value = result_set_->getString(i);  
                oss << col_name << " = \"" << value << "\"\n";
            } catch (const sql::SQLException& e) {
                oss << col_name << " = <ERROR: " << e.what() << ">\n";
            }
        }
        oss << "--------\n";
    }

    if (row_num == 0) {
        oss << "(no rows)\n";
    } else {
        oss << "Total rows: " << row_num << "\n";
    }


    return oss.str();
}

Objects MySQLResultSet::to_vector_of_maps(){
    std::vector<std::unordered_map<std::string, std::string>> rows;

    if (!result_set_) {
        return rows;
    }

    sql::ResultSetMetaData* meta = result_set_->getMetaData();
    int col_count = meta->getColumnCount();

    while (result_set_->next()) {
        std::unordered_map<std::string, std::string> row;
        row.reserve(col_count);

        for (int i = 1; i <= col_count; ++i) {
            std::string col_name = meta->getColumnLabel(i);  
            try {
                std::string value = result_set_->getString(i);
                row[col_name] = value;
            } catch (const sql::SQLException& e) {
                row[col_name] = "<ERROR: " + std::string(e.what()) + ">";
            }
        }
        rows.push_back(std::move(row));
    }

    return rows;
}
}}// namespace quick::ultra
