#ifndef QUICK_ULTRA_EXPR_HPP
#define QUICK_ULTRA_EXPR_HPP
#include <string>


namespace quick::ultra::sqljke{

enum SIGN{
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

std::string signToString(SIGN sign);

class Expression
{
private:
    std::string field_;
    SIGN sign_;
    std::string value_;
public:
    Expression(std::string field, SIGN sign, std::string value);
    Expression(std::string field, SIGN sign);
    ~Expression();

    std::string field();
    SIGN sign();
    std::string value();

    std::string get();
};

}
#endif
