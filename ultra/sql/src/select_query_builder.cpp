#include "select_query_builder.hpp"
#include "select_query_ir.hpp"
#include <iostream>
namespace quick::ultra::sqljke{

SelectQueryBuilder::SelectQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect) {}

void SelectQueryBuilder::set_select_list(const std::vector<std::variant<Column, Aggregate, Scalar>> select_list){
    select_list_ = select_list;
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
    return *this;
} 

SelectQueryBuilder& SelectQueryBuilder::having(Expression expression){
    having_clause_ = dialect_->having_clause(expression);
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::order_by(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs){
    order_by_clause_ = dialect_->order_by_clause(column_dirs);
    return *this;
} 

std::string SelectQueryBuilder::build() {

    SelectQueryIR ir;
    ir.select_list = select_list_;
    ir.table_name = table_name_; 
    ir.where_clauses = where_clauses_;
    ir.group_by_columns = group_by_clause_;
    ir.order_by_columns = order_by_clause_;
    if (limit_ > 0) {
        ir.limit_offset = std::make_pair(limit_, offset_);
    } else {
        ir.limit_offset = std::nullopt;
    }
    ir.having_clause = having_clause_.empty() ? std::nullopt : std::make_optional(having_clause_);

    auto sql = dialect_->compile_select(ir);

    std::cout << sql << std::endl;
    return sql;
    
}



}
