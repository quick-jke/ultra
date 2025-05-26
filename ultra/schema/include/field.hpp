#ifndef QUICK_ULTRA_SCHEMA_FIELD_HPP
#define QUICK_ULTRA_SCHEMA_FIELD_HPP

#include "option.hpp"
#include "sqlvar.hpp"
#include <string>
#include <set>
#include <iostream>

namespace quick{
namespace ultra{

class Field{
public:
    Field(const std::string& name, SQLVAR type, bool id);

    const std::string& getName() const;
    SQLVAR getType();
    std::string toString();

    bool operator<(const Field& other) const {
        return std::tie(name_) < std::tie(other.getName());
    }
    bool isIdentity();

private:
    std::string name_;
    SQLVAR type_;
    bool is_identity_;
};

}}

#endif