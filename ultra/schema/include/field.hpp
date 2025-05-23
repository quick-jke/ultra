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
    Field(const std::string& name, SQLVAR type, std::set<OPTION> options);

    std::string getSQLNormalize();
    
    const std::string& getName() const;

    std::string toString();

    std::set<OPTION> getOptions();

    

    SQLVAR getType();

    bool operator<(const Field& other) const {
        return std::tie(name_) < std::tie(other.getName());
    }

private:
    std::string name_;
    SQLVAR type_;
    std::set<OPTION> options_;
};

}}

#endif