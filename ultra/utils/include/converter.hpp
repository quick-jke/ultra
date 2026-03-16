#ifndef QUICK_ULTRA_UTILS_INCLUDE_CONVERTER_HPP
#define QUICK_ULTRA_UTILS_INCLUDE_CONVERTER_HPP
#include <variant>
#include <string>

std::string variant_to_string(std::variant<std::string, int, double, bool> const & value);


#endif
