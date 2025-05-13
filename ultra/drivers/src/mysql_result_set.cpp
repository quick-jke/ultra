
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
    return result_set_->getString(column).c_str(); // cppconn возвращает sql::SQLString
}

}
}