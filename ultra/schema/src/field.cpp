#include "field.hpp"

Field::Field(const std::string& name, const std::string& type, std::set<OPTION> options) : name_(name), type_(type), options_(options){}

std::string Field::getSQLNormalize(){
    std::string options;
    if(options_.count(OPTION::ID)){
        options += " INT PRIMARY KEY AUTO_INCREMENT";
    }
    return  "\t" + name_ + " " + type_ + options;
}

const std::string& Field::getName() const{
    return name_;
}

std::string Field::stringOptions(){
    std::string options;

    if(options_.size()){
        for(auto option : options_){
            switch (option)
            {
            case ID:{
                options += " ID";
                break;
            }
            case ONE_TO_MANY:{
                options += " ONE_TO_MANY";
                break;
            }
            case ONE_TO_ONE:{
                options += " ONE_TO_ONE";
                break;
            }
            case MANY_TO_MANY:{
                options += " MANY_TO_MANY";
                break;
            }
            case MANY_TO_ONE:{
                options += " MANY_TO_ONE";
                break;
            }
            
            default:
                break;
            }
        }
    }

    return "[" + options + "]";
}

std::string Field::toString(){
    std::string options;

    if(options_.size()){
        for(auto option : options_){
            switch (option)
            {
            case ID:{
                options += " ID";
                break;
            }
            case ONE_TO_MANY:{
                options += " ONE_TO_MANY";
                break;
            }
            case ONE_TO_ONE:{
                options += " ONE_TO_ONE";
                break;
            }
            case MANY_TO_MANY:{
                options += " MANY_TO_MANY";
                break;
            }
            case MANY_TO_ONE:{
                options += " MANY_TO_ONE";
                break;
            }
            
            default:
                break;
            }
        }
    }
    
    return "\tfield{ name: " + name_ + ", type: " + type_ + (options_.size() ? ", options: [" + options + " ]}" : "");  
}

std::set<OPTION> Field::getOptions(){
    return options_;
}

std::string Field::getType(){
    return type_;
}







