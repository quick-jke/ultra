#ifndef DRIVER_MYSQL_RESULT_SET_HPP
#define DRIVER_MYSQL_RESULT_SET_HPP
#include "iresult_set.hpp"
#include <sstream>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
namespace quick {
namespace ultra {
class MySQLResultSet : public ResultSet {
public:
    explicit MySQLResultSet(sql::ResultSet* rs);
    ~MySQLResultSet() override;

    bool next() override;
    int get_int(const std::string& column) override;
    std::string get_string(const std::string& column) override;
    bool get_bool(const std::string& column) override;
    double get_double(const std::string& column) override;
    char get_char(const std::string& column) override;
    std::string debug(const std::vector<std::string>& columns) override;

private:
    std::unique_ptr<sql::ResultSet> result_set_;
};
}}// namespace quick::ultra
#endif
