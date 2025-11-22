#ifndef QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#define QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#include "column.hpp"
#include "eaggregate.hpp"
#include <optional>
namespace quick::ultra::sqljke{


struct Aggregate{
    EAggregate type_;
    Column col_;
    std::optional<std::string> alias_ = std::nullopt;
    std::string aggregate_to_string(){
        switch (type_){
            case EAggregate::MIN   : return "MIN(" + col_.get() + ")" + (alias_.has_value() ? " AS " + *alias_ : "");
            case EAggregate::MAX   : return "MAX(" + col_.get() + ")" + (alias_.has_value() ? " AS " + *alias_ : "");
            case EAggregate::AVG   : return "AVG(" + col_.get() + ")" + (alias_.has_value() ? " AS " + *alias_ : "");
            case EAggregate::COUNT : return "COUNT(" + col_.get() + ")" + (alias_.has_value() ? " AS " + *alias_ : "");
            case EAggregate::SUM   : return "SUM(" + col_.get() + ")" + (alias_.has_value() ? " AS " + *alias_ : "");
            default                : return "UNKNOW";
        }
    }
    Aggregate& as(const std::string& alias){ 
        alias_ = alias; 
        return *this;
    }

    std::optional<std::string> alias(){
        return alias_;
    }
};


inline Aggregate count(const Column& col) {
    return {EAggregate::COUNT, col};
}
inline Aggregate avg(const Column& col) {
    return {EAggregate::AVG, col};
}
inline Aggregate min(const Column& col) { return {EAggregate::MIN, col}; }
inline Aggregate max(const Column& col) { return {EAggregate::MAX, col}; }

}

#endif
