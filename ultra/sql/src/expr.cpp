#include "expr.hpp"
#include <stdexcept>
namespace quick::ultra::sqljke{


Expression::Expression(std::string field, SIGN sign, std::string value) : field_(field), sign_(sign), value_(value) {}
Expression::Expression(std::string field, SIGN sign) : field_(field), sign_(sign) {}
Expression::~Expression() {}

std::string Expression::field() { return field_; }
SIGN Expression::sign() { return sign_; }
std::string Expression::value() { return value_; }


std::string Expression::get() {
    switch (sign_) {
        case IS_NULL:       return field_ + " IS NULL";
        case IS_NOT_NULL:   return field_ + " IS NOT NULL";
        case IS_TRUE:       return field_ + " IS TRUE";
        case IS_FALSE:      return field_ + " IS FALSE";
        
        case BETWEEN_AND:
        return field_ + " BETWEEN " + value_;
        
        case IN:
        return " IN " + field_;
        
        default:
        return field_ + " " + signToString(sign_) + " " + value_;
    }
}

std::string signToString(SIGN sign) {
    switch (sign) {
        case MORE_THAN:       return ">";
        case LESS_THAN:       return "<";
        case MORE_OR_EQUAL:   return ">=";
        case LESS_OR_EQUAL:   return "<=";
        case EQUAL:           return "=";
        case NOT_EQUAL:       return "!=";
        case LIKE:            return "LIKE";
        case IS_TRUE:         return "IS TRUE";
        case IS_FALSE:        return "IS FALSE";
        case IS_NULL:         return "IS NULL";
        case IS_NOT_NULL:     return "IS NOT NULL";
        default:
            throw std::invalid_argument("Unknown SIGN value");
    }
}

}
