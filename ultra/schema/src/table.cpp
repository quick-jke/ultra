#include "table.hpp"
namespace quick{
namespace ultra{
Table::Table(){}

Table::Table(const std::string& name, std::set<Field> fields) 
    : name_(name), fields_(fields){}

const std::string& Table::getName() const {
    return name_;
}

const std::set<Field>& Table::getFields() const {
    return fields_;
}



std::string Table::toString(){
    std::string fields;
    for(auto field : fields_){
        fields += field.toString() + "\n";
    }

    return "Table:\n\t" + name_ + "\nfields\n" + fields + "\n==============\n";
}

}}