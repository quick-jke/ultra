#include "column.hpp"
namespace quick::ultra::sqljke{
Column::Column(std::string name, TYPE type, bool is_primary_key, bool is_auto_increment, bool is_nullable, bool is_unique, std::string default_value)
        : name_(name), type_(type), is_primary_key_(is_primary_key), is_auto_increment_(is_auto_increment), is_nullable_(is_nullable), is_unique_(is_unique), default_value_(default_value) {}
    
Column::Column(std::string name) : name_(name) {}

Column& Column::as(std::string alias) {
    alias_ = alias;
    return *this;
}
std::string Column::get() const {
    return name_;
}
std::string Column::name() const {
    return name_;
}

TYPE Column::type() const {
    return type_;
}

bool Column::is_nullable(){
    return is_nullable_;
}

bool Column::is_primary_key(){
    return is_primary_key_;
}

bool Column::is_auto_increment(){
    return is_auto_increment_;
}

bool Column::is_unique() {
    return is_unique_;
}

std::string Column::default_value(){
    return default_value_;
}


}
