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
    std::string default_value_;
    std::optional<std::string> alias_ = std::nullopt;
public:
    Column(std::string name, TYPE type, bool is_primary_key, bool is_auto_increment, bool is_nullable, std::string default_value)
        : name_(name), type_(type), is_primary_key_(is_primary_key), is_auto_increment_(is_auto_increment), is_nullable_(is_nullable), default_value_(default_value) {}
    Column(std::string name) : name_(name) {}
    Column& as(std::string alias) {
        alias_ = alias;
        return *this;
    }
    const std::string& get() {
        return name_;
    }
    std::string name() const {
        return name_;
    }

    TYPE type() const {
        return type_;
    }

    bool is_nullable(){
        return is_nullable_;
    }
    
    bool is_primary_key(){
        return is_primary_key_;
    }
    
    bool is_auto_increment(){
        return is_auto_increment_;
    }
    
    std::string default_value(){
        return default_value_;
    }
};
}// namespace quick::ultra::sqljke
#endif
