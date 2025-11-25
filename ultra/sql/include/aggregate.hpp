#ifndef QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#define QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#include "column.hpp"
#include "eaggregate.hpp"
#include <optional>
namespace quick::ultra::sqljke{


struct Aggregate{
    AGGREGATE type_;
    Column col_;
    std::optional<std::string> alias_ = std::nullopt;
    std::string to_string(){
        std::stringstream oss;
        switch (type_){
            case AGGREGATE::MIN   : { oss << "MIN("; break; }
            case AGGREGATE::MAX   : { oss << "MAX("; break; }
            case AGGREGATE::AVG   : { oss << "AVG("; break; }
            case AGGREGATE::COUNT : { oss << "COUNT("; break; }
            case AGGREGATE::SUM   : { oss << "SUM("; break; }
            default: { return "UNKNOWN"; }
        }
        return oss.str() + col_.get() + ")" + (alias_.has_value() ? " AS " + *alias_ : "");

    }

    Aggregate& as(const std::string& alias){ 
        alias_ = alias; 
        return *this;
    }

    std::optional<std::string> alias(){
        return alias_;
    }
};


inline Aggregate count(const Column& col = Column{.name = "*"}) {
    return {AGGREGATE::COUNT, col};
}
inline Aggregate avg(const Column& col) {
    return {AGGREGATE::AVG, col};
}
inline Aggregate min(const Column& col) { return {AGGREGATE::MIN, col}; }
inline Aggregate max(const Column& col) { return {AGGREGATE::MAX, col}; }
inline Aggregate sum(const Column& col) { return {AGGREGATE::SUM, col}; }
}

#endif
