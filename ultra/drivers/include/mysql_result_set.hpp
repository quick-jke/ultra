#ifndef DRIVER_MYSQL_RESULT_SET_HPP
#define DRIVER_MYSQL_RESULT_SET_HPP


#include "result_set.hpp"
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

private:
    std::unique_ptr<sql::ResultSet> result_set_;
};

}
}

#endif