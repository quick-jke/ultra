#include "select_query_builder.hpp"
#include "select_query_ir.hpp"
#include <iostream>
namespace quick::ultra::sqljke{

void SelectQueryBuilder::set_select_list(const std::vector<std::variant<Column, Aggregate, Scalar>> select_list){
    select_list_ = select_list;
}

SelectQueryBuilder& SelectQueryBuilder::from(const Table& table) {
    table_ = &table;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::where(const Expression& expression) {
    where_clauses_.push_back(expression);  
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::limit(int limit, int offset) {
    limit_ = limit;
    offset_ = offset;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::group_by(const std::vector<Column>& columns){
    group_by_columns_ = columns;
    return *this;
} 

SelectQueryBuilder& SelectQueryBuilder::having(const Expression& expression){
    having_clause_ = expression;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::order_by(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs){
    order_by_columns_ = column_dirs;
    return *this;
} 

std::string SelectQueryBuilder::build() const {

    SelectQueryIR ir;
    ir.select_list = select_list_;
    ir.table = table_;
    ir.where_clauses = where_clauses_;
    ir.group_by_columns = group_by_columns_;
    ir.order_by_columns = order_by_columns_;      
    ir.having_clause = having_clause_;            
    
    if (limit_ > 0) {
        ir.limit_offset = std::make_pair(limit_, offset_);
    }
    
    auto sql = dialect_->compile_select(ir);

    std::cout << sql << std::endl;
    return sql;
    
}

void SelectQueryBuilder::reset() {
    select_list_.clear();
    table_ = nullptr;
    where_clauses_.clear();
    group_by_columns_ = std::nullopt;
    order_by_columns_ = std::nullopt;
    having_clause_ = std::nullopt;
    limit_ = -1;
    offset_ = 0;
}



}
