#ifndef QUICK_ULTRA_SCHEMA_OPTION_HPP
#define QUICK_ULTRA_SCHEMA_OPTION_HPP
#include <string>
namespace quick{
namespace ultra{

enum OPTION {

    ONE_TO_ONE,
    ONE_TO_MANY,
    MANY_TO_MANY,
    MANY_TO_ONE,
    ID
};

inline std::string optionToString(OPTION option) {
    switch (option) {
        case OPTION::ONE_TO_ONE:    return "ONE_TO_ONE";
        case OPTION::ONE_TO_MANY:   return "ONE_TO_MANY";
        case OPTION::MANY_TO_MANY:  return "MANY_TO_MANY";
        case OPTION::MANY_TO_ONE:   return "MANY_TO_ONE";
        case OPTION::ID:            return "ID";
        default:                    return "UNKNOWN";
    }
}

}}

#endif