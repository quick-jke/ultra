#ifndef DRIVER_FACTORY_HPP
#define DRIVER_FACTORY_HPP
#include "idriver.hpp"
#include <memory>
#include <string>
#include <stdexcept>
namespace quick {
namespace ultra {
enum class DRIVER_TYPE{
    MY_SQL,
    POSTGRE_SQL,
    MS_SQL,
    ORACLE
};
class DriverFactory {
public:
    static std::shared_ptr<IDriver> create(const DRIVER_TYPE& driver_type);
};
}}// namespace quick::ultra
#endif
