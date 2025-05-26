#ifndef QUICK_ULTRA_SCHEMA_OPTION_HPP
#define QUICK_ULTRA_SCHEMA_OPTION_HPP
#include <string>
namespace quick{
namespace ultra{

enum OPTION {
    UNKNOWN,
    ONE_TO_ONE,
    ONE_TO_MANY,
    MANY_TO_MANY,
    MANY_TO_ONE,
    ID
};


inline OPTION stringToOptionString(const std::string& str) {
    if (str == "ONE_TO_ONE") {
        return ONE_TO_ONE;
    }else if (str == "ONE_TO_MANY") {
        return ONE_TO_MANY;
    }
    else if (str == "MANY_TO_MANY") {
        return MANY_TO_MANY;
    }
    else if (str == "MANY_TO_ONE") {
        return MANY_TO_ONE;
    }
    else if (str == "ID") {
        return ID;
    }
    return UNKNOWN;
}

inline std::string optionToString(OPTION op) {
    switch (op)
    {
    case UNKNOWN:
        return "UNKNOWN";
        break;
    case ONE_TO_ONE:
        return "ONE_TO_ONE";
        break;
    case ONE_TO_MANY:
        return "ONE_TO_MANY";
        break;
    case MANY_TO_MANY:
        return "MANY_TO_MANY";
        break;
    case MANY_TO_ONE:
        return "MANY_TO_ONE";
        break;
    case ID:
        return "ID";
        break;
    default:
        
        break;
    }
    return "";
}


}}

#endif