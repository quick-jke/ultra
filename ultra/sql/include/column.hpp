#ifndef QUICK_ULTRA_SQL_INCLUDE_COLUMN_HPP
#define QUICK_ULTRA_SQL_INCLUDE_COLUMN_HPP
#include <string>
#include <optional>
#include "type.hpp"
namespace quick::ultra::sqljke{
class Column {
private:
    std::string name_;
    TYPE type_;
    bool is_primary_key_ = false;
    bool is_auto_increment_ = false;
    bool is_nullable_ = true;
    bool is_unique_ = false;
    std::string default_value_;
    std::optional<std::string> alias_ = std::nullopt;
public:
    Column(std::string name, TYPE type, bool is_primary_key, bool is_auto_increment, bool is_nullable, std::string default_value);
    
    Column(std::string name);

    Column& as(std::string alias);
    std::string get() const;
    std::string name() const;

    TYPE type() const;

    bool is_nullable();
    
    bool is_primary_key();
    
    bool is_auto_increment();

    bool is_unique();
    
    std::string default_value();
};
}// namespace quick::ultra::sqljke
#endif
