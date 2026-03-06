#include "aggregate.hpp"
#include <sstream>

namespace quick::ultra::sqljke{

Aggregate::Aggregate(AGGREGATE type, Column col) : type_(type), col_(col){}

std::string Aggregate::to_string(){
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

Aggregate& Aggregate::as(const std::string& alias){ 
    alias_ = alias; 
    return *this;
}

std::optional<std::string> Aggregate::alias(){
    return alias_;
}
}
