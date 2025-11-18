#ifndef QUICK_ULTRA_EXPR_HPP
#define QUICK_ULTRA_EXPR_HPP
#include <string>
#include <variant>
namespace quick{
namespace ultra{
namespace sqljke{


enum SIGN{
    MORE_THAN,
    LESS_THAN,
    MORE_OR_EQUAL,
    LESS_OR_EQUAL,
    EQUAL,
    NOT_EQUAL,

    LIKE,

    IS_TRUE,
    IS_FALSE,

    IS_NULL,
    IS_NOT_NULL

};


class Expression
{
private:
    std::string field_;
    SIGN sign_;
    std::variant<double, int, std::string, bool> value_;
public:
    Expression(std::string field, SIGN sign, std::variant<double, int, std::string, bool> value)
        : field_(field), sign_(sign), value_(value) {}
    ~Expression() {}

    std::string field() { return field_; }
    SIGN sign() { return sign_; }
    std::variant<double, int, std::string, bool> value() { return value_; }
};



}}}
#endif
