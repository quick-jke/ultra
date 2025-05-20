#ifndef QUICK_ULTRA_SCHEMA_TABLE_HPP
#define QUICK_ULTRA_SCHEMA_TABLE_HPP

#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <map>
#include "field.hpp"

namespace quick{
namespace ultra{


class Table{
public:
    Table(const std::string& name, std::set<Field> fields);
    Table();
    const std::string& getName() const;
    const std::set<Field>& getFields() const;

    std::string toString();

    bool operator<(const Table& other) const {
        return std::tie(name_) < std::tie(other.getName());
    }

private:
    std::string name_;
    std::set<Field> fields_;

};
}}


#endif