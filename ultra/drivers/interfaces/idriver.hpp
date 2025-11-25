#ifndef QUICK_ULTRA_DRIVERS_INTERFACES_DRIVER_HPP
#define QUICK_ULTRA_DRIVERS_INTERFACES_DRIVER_HPP
#include <string>
#include <memory>
#include "driver_type.hpp"
namespace quick {
namespace ultra {
class IDriver {
public:
    virtual ~IDriver() = default;

    virtual bool connect(const std::string& connection_string) = 0;
    virtual void disconnect() = 0;
    virtual void execute(const std::string& sql) = 0;
    virtual std::unique_ptr<class ResultSet> query(const std::string& sql) = 0;

    virtual void begin_transaction() = 0;
    virtual void commit() = 0;
    virtual void rollback() = 0;
    virtual DRIVER_TYPE type() const = 0;
    virtual int get_last_insert_id() const = 0;

};
}}// namespace quick::ultra
#endif
