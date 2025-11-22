#ifndef QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#define QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#include "column.hpp"
#include "eaggregate.hpp"
namespace quick::ultra::sqljke{


struct Aggregate{
    EAggregate type_;
    Column col_;
    std::string aggregate_to_string(){
        switch (type_){
            case EAggregate::MIN   : return "MIN(" + col_.get() + ")";
            case EAggregate::MAX   : return "MAX(" + col_.get() + ")";
            case EAggregate::AVG   : return "AVG(" + col_.get() + ")";
            case EAggregate::COUNT : return "COUNT(" + col_.get() + ")";
            case EAggregate::SUM   : return "SUM(" + col_.get() + ")";
            default                : return "UNKNOW";
        }
    }
    std::string as(const std::string& name){
        return " AS " + name;
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
