#include "value.hpp"

namespace quick::ultra::sqljke{

Value::Value(std::variant<std::string, int, double, bool> value, TYPE type)
    : value_(value), type_(type){}


}
