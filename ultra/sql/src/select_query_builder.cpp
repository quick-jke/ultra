#include "select_query_builder.hpp"
#include <iostream>
namespace quick::ultra::sqljke{

SelectQueryBuilder::SelectQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect) {}

void SelectQueryBuilder::set_columns(const std::vector<Column>& columns){
    columns_ = columns;
}

void SelectQueryBuilder::set_aggregate(const Aggregate aggregate){
    is_aggregate_ = true;
    aggregate_ = aggregate;
}

SelectQueryBuilder& SelectQueryBuilder::from(Table table) {
    table_name_ = dialect_->quote_identifier(table);
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::where(Expression expression) {
    where_clauses_.push_back(expression.get());
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::limit(int limit, int offset) {
    limit_ = limit;
    offset_ = offset;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::group_by(const std::vector<Column>& columns){
    group_by_clause_ = dialect_->group_by_clause(columns);
    is_aggregate_ = true;
    return *this;
} 

SelectQueryBuilder& SelectQueryBuilder::having(Expression expression){
    having_clause_ = dialect_->having_clause(expression);
    is_aggregate_ = true;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::order_by(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs){
    order_by_clause_ = dialect_->order_by_clause(column_dirs);
    return *this;
} 

std::string SelectQueryBuilder::build() {
    std::ostringstream oss;
    oss << "SELECT ";

    if(is_aggregate_){
        oss << dialect_->aggregate_clause(aggregate_);
    }else{
        if (columns_.empty()) {
            oss << "*";
        } else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                if (i > 0) oss << ", ";
                Column col = columns_.at(i);
                oss << dialect_->quote_identifier(col.get());
            }
        }
    }
    

    oss << " FROM " << table_name_;

    if (!where_clauses_.empty()) {
        oss << " WHERE ";
        for (size_t i = 0; i < where_clauses_.size(); ++i) {
            if (i > 0) oss << " AND ";
            oss << where_clauses_[i];
        }
    }
    if(!group_by_clause_.empty()){
        oss << " " << group_by_clause_;
    }
    if(!order_by_clause_.empty()){
        oss << " " << order_by_clause_;
    }
    if (limit_ > 0) {
        oss << " " << dialect_->limit_clause(limit_, offset_);
    }
    
    if(!having_clause_.empty()){
        oss << " " << having_clause_;
    }
    std::cout << "[DEBUG:QUERY] " << oss.str() << std::endl;
    return oss.str();
}



}
