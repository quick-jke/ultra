#include "mysql_result_set.hpp"
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
std::string MySQLResultSet::debug(const std::vector<std::string>& columns){
    std::stringstream oss;
    while (next()) {
        oss << "Row:\n";
        for (const auto& col : columns) {
            oss << "  " << col << ": " << get_string(col) << "\n";
        }
        oss << "--------\n";
    }

    return oss.str();
}
}}// namespace quick::ultra
