#ifndef QUICK_ULTRA_SQL_ENUM_EXPR_HPP
#define QUICK_ULTRA_SQL_ENUM_EXPR_HPP
#include <string>
#include <sstream>
#include <vector>
#include "sign.hpp"
#include "column.hpp"
namespace quick::ultra::sqljke{
std::string signToString(SIGN sign);

class Expression
{
private:
    std::string field_;
    SIGN sign_;
    std::string value_;
    std::string value2_;
public:
    Expression(std::string field, SIGN sign, std::string value1, std::string value2);
    Expression(std::string field, SIGN sign, std::string value);
    Expression(std::string field, SIGN sign);
    ~Expression();

    std::string field();
    SIGN sign();
    std::string value();

    std::string get();

//-------------------
public:
    explicit Expression(Column column){
        field_ = column.get();
    }

    template<typename T>
    Expression& more_than(T value){
        sign_ = SIGN::MORE_THAN;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& less_than(T value){
        sign_ = SIGN::LESS_THAN;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& more_or_equal(T value){
        sign_ = SIGN::MORE_OR_EQUAL;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& less_or_equal(T value){
        sign_ = SIGN::LESS_OR_EQUAL;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& equal(T value){
        sign_ = SIGN::EQUAL;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& not_equal(T value){
        sign_ = SIGN::NOT_EQUAL;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& between_and(T value1, T value2){
        sign_ = SIGN::BETWEEN_AND;
        value_ = std::to_string(value1);
        value2_ = std::to_string(value2);
        return *this;
    }

    template<typename T>
    Expression& like(T value){
        sign_ = SIGN::LIKE;
        value_ = std::to_string(value);
        return *this;
    }

    template<typename T>
    Expression& is_true(T value){
        sign_ = SIGN::IS_TRUE;
        return *this;
    }

    template<typename T>
    Expression& is_false(T value){
        sign_ = SIGN::IS_FALSE;
        return *this;
    }

    template<typename T>
    Expression& is_null(T value){
        sign_ = SIGN::IS_NULL;
        return *this;
    }
    
    template<typename T>
    Expression& is_not_null(T value){
        sign_ = SIGN::IS_NOT_NULL;
        return *this;
    }
    
    template<typename T>
    Expression& in(std::vector<T> values){
        std::stringstream oss;
		oss << "(";
		for(size_t i = 0; i < values.size(); ++i){
			oss << values.at(i);
			if(i != values.size() - 1){
				oss << ", ";
			}
		}
		oss << ")";
        sign_ = SIGN::IN;
        value_ = oss.str();
        return *this;
    }

};

}
#endif
