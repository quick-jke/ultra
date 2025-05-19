#ifndef FIELD
#define FIELD

#include "option.hpp"
#include "var.hpp"
#include <string>
#include <set>
#include <iostream>
#include "sql.hpp"

class Field{
public:
    Field(const std::string& name, const std::string& type, std::set<OPTION> options);

    std::string getSQLNormalize();
    
    const std::string& getName() const;

    std::string toString();

    std::set<OPTION> getOptions();

    std::string stringOptions();

    std::string getType();

    bool operator<(const Field& other) const {
        return std::tie(name_) < std::tie(other.getName());
    }

private:
    std::string name_;
    std::string type_;
    // VAR type_;
    std::set<OPTION> options_;
};

#endif