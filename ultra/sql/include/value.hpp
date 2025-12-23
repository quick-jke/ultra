#ifndef QUICK_ULTRA_SQL_INCLUDE_VALUE_HPP
#define QUICK_ULTRA_SQL_INCLUDE_VALUE_HPP
#include <variant>
#include <string>
#include "type.hpp"
namespace quick::ultra::sqljke{
class Value{
public:
    Value(std::variant<std::string, int, double, bool> value, TYPE type);

private:
    std::variant<std::string, int, double, bool> value_; 
    TYPE type_;
};
}
#endif
