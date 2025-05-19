#ifndef TABLE
#define TABLE

#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <map>
#include "field.hpp"


class Table{
public:
    Table(const std::string& name, std::set<Field> fields, std::set<std::string> dependencies);
    Table();
    const std::string& getName() const;
    const std::set<Field>& getFields() const;
    std::set<std::string> getDependencies();

    std::string toString();

    bool operator<(const Table& other) const {
        return std::tie(name_) < std::tie(other.getName());
    }

private:
    std::string name_;
    std::set<Field> fields_;
    std::set<std::string> dependencies_;

};


#endif