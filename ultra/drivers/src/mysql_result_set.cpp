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
            std::string col_name = meta->getColumnName(i);
            try {
                std::string value = result_set_->getString(i);  
                oss << "  [" << i << "] " << col_name << " = \"" << value << "\"\n";
            } catch (const sql::SQLException& e) {
                oss << "  [" << i << "] " << col_name << " = <ERROR: " << e.what() << ">\n";
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
}}// namespace quick::ultra
