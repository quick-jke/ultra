#ifndef QUICK_ULTRA_SQL_INCLUDE_COLUMN_HPP
#define QUICK_ULTRA_SQL_INCLUDE_COLUMN_HPP
#include <string>
#include <optional>
#include "type.hpp"
namespace quick::ultra::sqljke{
struct Column {
    std::string name;
    TYPE type;
    bool is_primary_key = false;
    bool is_auto_increment = false;
    bool is_nullable = true;
    std::string default_value;
    std::optional<std::string> alias_ = std::nullopt;

    Column& as(std::string alias) {
        alias_ = alias;
        return *this;
    }
    const std::string& get() {
        return name + (alias_.has_value() ? " AS " + *alias_ : "");
    }
};
}// namespace quick::ultra::sql
#endif
