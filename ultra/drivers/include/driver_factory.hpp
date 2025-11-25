#ifndef QUICK_ULTRA_DRIVERS_INCLUDE_DRIVER_FACTORY_HPP
#define QUICK_ULTRA_DRIVERS_INCLUDE_DRIVER_FACTORY_HPP
#include "idriver.hpp"
#include "driver_type.hpp"
#include <memory>
#include <string>
#include <stdexcept>
namespace quick::ultra {
class DriverFactory {
public:
    static std::shared_ptr<IDriver> create(const DRIVER_TYPE& driver_type);
};
}// namespace quick::ultra
#endif
