#ifndef DRIVER_INTERFACE_HPP
#define DRIVER_INTERFACE_HPP
#include <string>
#include <memory>
namespace quick {
namespace ultra {
enum class DriverType { MySQL, PostgreSQL, Unknown };
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
    virtual DriverType type() const = 0;
};
}}// namespace quick::ultra
#endif