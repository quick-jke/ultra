#ifndef QUICK_ULTRA_SQL_ENUM_SIGN_HPP
#define QUICK_ULTRA_SQL_ENUM_SIGN_HPP
#include <stdexcept>
namespace quick::ultra::sqljke{
enum class SIGN{
    MORE_THAN,
    LESS_THAN,
    MORE_OR_EQUAL,
    LESS_OR_EQUAL,
    EQUAL,
    NOT_EQUAL,

    BETWEEN_AND,

    LIKE,
    
    IS_TRUE,
    IS_FALSE,

    IS_NULL,
    IS_NOT_NULL,

    IN
};

inline std::string signToString(SIGN sign) {
    switch (sign) {
        case SIGN::MORE_THAN:       return ">";
        case SIGN::LESS_THAN:       return "<";
        case SIGN::MORE_OR_EQUAL:   return ">=";
        case SIGN::LESS_OR_EQUAL:   return "<=";
        case SIGN::EQUAL:           return "=";
        case SIGN::NOT_EQUAL:       return "!=";
        case SIGN::LIKE:            return "LIKE";
        case SIGN::IS_TRUE:         return "IS TRUE";
        case SIGN::IS_FALSE:        return "IS FALSE";
        case SIGN::IS_NULL:         return "IS NULL";
        case SIGN::IS_NOT_NULL:     return "IS NOT NULL";
        case SIGN::IN:              return "IN";
        default:
            throw std::invalid_argument("Unknown SIGN value");
    }
}
}
#endif
