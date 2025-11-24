#include "expr.hpp"
namespace quick::ultra::sqljke{

Expression::Expression(std::string field, SIGN sign, std::string value1, std::string value2) : field_(field), sign_(sign), value_(value1), value2_(value2) {}
Expression::Expression(std::string field, SIGN sign, std::string value) : field_(field), sign_(sign), value_(value) {}
Expression::Expression(std::string field, SIGN sign) : field_(field), sign_(sign) {}
Expression::~Expression() {}

std::string Expression::field() { return field_; }
SIGN Expression::sign() { return sign_; }
std::string Expression::value() { return value_; }


std::string Expression::get() {
    switch (sign_) {
        case SIGN::IS_NULL:       return field_ + " IS NULL";
        case SIGN::IS_NOT_NULL:   return field_ + " IS NOT NULL";
        case SIGN::IS_TRUE:       return field_ + " IS TRUE";
        case SIGN::IS_FALSE:      return field_ + " IS FALSE";
        case SIGN::BETWEEN_AND:   return field_ + " BETWEEN " + value_ + " AND " + value2_;
        default:            return field_ + " " + signToString(sign_) + " " + value_;
    }
}



}
