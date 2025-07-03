#ifndef QUICK_ULTRA_EXPR_HPP
#define QUICK_ULTRA_EXPR_HPP
#include <string>
#include <variant>
namespace quick{
namespace ultra{
namespace sqljke{


enum Expr{
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

struct ExprStruct{
    std::string field_;
    Expr expr_;
    std::variant<double, int, std::string, bool> value_;
};

}}}
#endif
