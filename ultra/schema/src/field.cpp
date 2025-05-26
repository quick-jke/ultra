#include "field.hpp"
namespace quick{
namespace ultra{
Field::Field(const std::string& name, SQLVAR type, bool id) : name_(name), type_(type), is_identity_(id){}

const std::string& Field::getName() const{
    return name_;
}

std::string Field::toString(){
    return "\tfield{ name: " + name_ + ", type: " + varToString(type_) + (is_identity_ ? " , ID" : "") + " }";
}

SQLVAR Field::getType(){
    return type_;
}

bool Field::isIdentity(){
    return is_identity_;
}

}}



