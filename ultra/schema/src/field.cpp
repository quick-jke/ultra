#include "field.hpp"
namespace quick{
namespace ultra{
Field::Field(const std::string& name, SQLVAR type, std::set<OPTION> options) : name_(name), type_(type), options_(options){}

std::string Field::getSQLNormalize(){
    std::string options;
    if(options_.count(OPTION::ID)){
        options += " INT PRIMARY KEY AUTO_INCREMENT";
    }
    return  "\t" + name_ + " " + options;
}

const std::string& Field::getName() const{
    return name_;
}



std::string Field::toString(){
    std::string options;

    if(options_.size()){
        for(auto option : options_){
            options += optionToString(option);
        }
    }
    
    return "\tfield{ name: " + name_ + 
    ", type: " + varToString(type_) + 
    (options_.size() ? ", options: [ " + options + " ]}" : "}");  
}

std::set<OPTION> Field::getOptions(){
    return options_;
}

SQLVAR Field::getType(){
    return type_;
}



}}



