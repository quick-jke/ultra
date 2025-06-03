#ifndef QUICK_ULTRA_COLUMN_HPP
#define QUICK_ULTRA_COLUMN_HPP
#include <string>
namespace quick{
namespace ultra{
struct Column {
    std::string name;
    std::string type;
    bool is_primary_key = false;
    bool is_auto_increment = false;
    bool is_nullable = true;
    std::string default_value;
};
}}// namespace quick::ultra
#endif