#include "mysql_driver.hpp"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
namespace quick {
namespace ultra {
MySQLDriver::MySQLDriver() = default;

MySQLDriver::~MySQLDriver() {
    disconnect();
}

bool MySQLDriver::connect(const std::string& connection_string) {
    try {
        std::string host, user, password, database;

        auto get_value = [&](const std::string& key) -> std::string {
            size_t pos = connection_string.find(key + "=");
            if (pos == std::string::npos) return "";
            pos += key.size() + 1;
            size_t end_pos = connection_string.find(";", pos);
            return connection_string.substr(pos, end_pos - pos);
        };

        host = get_value("host");
        user = get_value("user");
        password = get_value("password");
        database = get_value("database");

        if (host.empty() || user.empty()) {
            std::cerr << "Missing required connection parameters" << std::endl;
            return false;
        }

        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        connection_.reset(driver->connect(host, user, password));

        std::unique_ptr<sql::Statement> stmt(connection_->createStatement());

        stmt->execute("CREATE DATABASE IF NOT EXISTS " + database);

        connection_->setSchema(database);

        return true;

    } catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << ", Code: " << e.getErrorCode() << std::endl;
        return false;
    }
}
void MySQLDriver::disconnect() {
    connection_.reset(); 
}

void MySQLDriver::execute(const std::string& sql) {
    if (!connection_) {
        throw std::runtime_error("Not connected to the database");
    }

    std::unique_ptr<sql::Statement> stmt(connection_->createStatement());
    stmt->execute(sql);
}

std::unique_ptr<ResultSet> MySQLDriver::query(const std::string& sql) {
    if (!connection_) {
        throw std::runtime_error("Not connected to the database");
    }

    std::unique_ptr<sql::Statement> stmt(connection_->createStatement());
    std::unique_ptr<sql::ResultSet> result_set(stmt->executeQuery(sql));

    return std::make_unique<MySQLResultSet>(result_set.release());
}

void MySQLDriver::begin_transaction() {
    if (!connection_) {
        throw std::runtime_error("Not connected to the database");
    }
    connection_->setAutoCommit(false);
}

void MySQLDriver::commit() {
    if (!connection_) {
        throw std::runtime_error("Not connected to the database");
    }
    connection_->commit();
    connection_->setAutoCommit(true);
}

void MySQLDriver::rollback() {
    if (!connection_) {
        throw std::runtime_error("Not connected to the database");
    }
    connection_->rollback();
    connection_->setAutoCommit(true);
}

DriverType MySQLDriver::type() const {
    return DriverType::MySQL;
}
}}// namespace quick::ultra