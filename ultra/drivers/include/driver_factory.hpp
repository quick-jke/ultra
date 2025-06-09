#ifndef DRIVER_FACTORY_HPP
#define DRIVER_FACTORY_HPP
#include "idriver.hpp"
#include <memory>
#include <string>
#include <stdexcept>
namespace quick {
namespace ultra {
class DriverFactory {
public:
    static std::shared_ptr<IDriver> create(const std::string& driver_type);
};
}}// namespace quick::ultra
#endif