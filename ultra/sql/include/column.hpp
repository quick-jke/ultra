#ifndef QUICK_ULTRA_SQL_INCLUDE_COLUMN_HPP
#define QUICK_ULTRA_SQL_INCLUDE_COLUMN_HPP
#include <string>
#include "expr.hpp"
#include "type.hpp"
namespace quick{
namespace ultra{
namespace sqljke{
struct Column {
    std::string name;
    Type type;
    bool is_primary_key = false;
    bool is_auto_increment = false;
    bool is_nullable = true;
    std::string default_value;
    const std::string& get() {
        return name;
    }
};
}}}// namespace quick::ultra::sql
#endif
