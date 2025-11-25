#ifndef QUICK_ULTRA_SQL_INCLUDE_SCALAR_HPP
#define QUICK_ULTRA_SQL_INCLUDE_SCALAR_HPP
#include <optional>
#include <sstream>
#include "aggregate.hpp"
#include "escalar.hpp"
namespace quick::ultra::sqljke{

struct Scalar{
    SCALAR type_; 
    std::optional<Aggregate> inner_ = std::nullopt;
    std::optional<int> value_ = std::nullopt;
    std::optional<std::string> alias_ = std::nullopt;
    std::string to_string(){
        std::stringstream oss;
        switch (type_){
            
            case SCALAR::ROUND : { 
                return "ROUND(" + (inner_.has_value() ? inner_->to_string() : "") + ", " + (value_.has_value() ? std::to_string(*value_) : " ") + ")" + (alias_.has_value() ? " AS " + *alias_ : "");
            }
            
            default: return "UNKNOWN";
        }
    }
    Scalar& as(const std::string& alias){ 
        alias_ = alias; 
        return *this;
    }

    std::optional<std::string> alias(){
        return alias_;
    }

};

inline Scalar round(const Aggregate& agg, int value){
    return {SCALAR::ROUND, agg, value};
}
}
#endif
