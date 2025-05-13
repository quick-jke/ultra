#ifndef DRIVER_MYSQL_DRIVER_HPP
#define DRIVER_MYSQL_DRIVER_HPP
#include "idriver.hpp"
#include "mysql_result_set.hpp"
#include <memory>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

namespace quick {
namespace ultra {

class MySQLDriver : public IDriver {
public:
    MySQLDriver();
    ~MySQLDriver() override;

    bool connect(const std::string& connection_string) override;
    void disconnect() override;

    void execute(const std::string& sql) override;
    std::unique_ptr<ResultSet> query(const std::string& sql) override;

    void begin_transaction() override;
    void commit() override;
    void rollback() override;

private:
    std::unique_ptr<sql::Connection> connection_;
};

}
}
#endif