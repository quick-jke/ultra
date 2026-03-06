#ifndef QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#define QUICK_ULTRA_SQL_INCLUDE_AGGREGATE_HPP
#include "column.hpp"
#include "eaggregate.hpp"
#include <optional>

namespace quick::ultra::sqljke{

class Aggregate{
public:
    Aggregate(AGGREGATE type, Column col);
    std::string to_string();
    Aggregate& as(const std::string& alias);
    std::optional<std::string> alias();

private:
    AGGREGATE type_;
    Column col_;
    std::optional<std::string> alias_ = std::nullopt;
};


inline Aggregate count(const Column& col = Column{"*"}) { return {AGGREGATE::COUNT, col}; }
inline Aggregate avg(const Column& col) { return {AGGREGATE::AVG, col}; }
inline Aggregate min(const Column& col) { return {AGGREGATE::MIN, col}; }
inline Aggregate max(const Column& col) { return {AGGREGATE::MAX, col}; }
inline Aggregate sum(const Column& col) { return {AGGREGATE::SUM, col}; }
}

#endif
