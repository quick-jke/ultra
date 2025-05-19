#include "table.hpp"
Table::Table(){}

Table::Table(const std::string& name, std::set<Field> fields, std::set<std::string> dependencies) 
    : name_(name), fields_(fields), dependencies_(dependencies){}

const std::string& Table::getName() const {
    return name_;
}

const std::set<Field>& Table::getFields() const {
    return fields_;
}

std::set<std::string> Table::getDependencies(){
    return dependencies_;
}

std::string Table::toString(){
    std::string fields;
    std::string dependencies;
    for(auto field : fields_){
        fields += field.toString() + "\n";
    }

    

    for(auto dep : dependencies_){
        dependencies += " " + dep;
    }
    // return "Table:\n\t" + name_ + "\nfields\n" + fields + "\ndeps:\n\t[" + dependencies + "]\n\n";
    return "Table:\n\t" + name_ + "\nfields\n" + fields + "\n==============\n";
}