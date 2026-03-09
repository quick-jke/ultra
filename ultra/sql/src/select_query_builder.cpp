#include "select_query_builder.hpp"
#include "select_query_ir.hpp"
#include <iostream>
namespace quick::ultra::sqljke{

void SelectQueryBuilder::set_select_list(const std::vector<std::variant<Column, Aggregate, Scalar>> select_list){
    ir_->select_list = select_list;
}

SelectQueryBuilder& SelectQueryBuilder::from(const Table& table) {
    ir_->table = &table;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::where(const Expression& expression) {
    ir_->where_clauses.push_back(expression);  
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::limit(int limit, int offset) {
    ir_->limit_offset = {limit, offset};
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::group_by(const std::vector<Column>& columns){
    ir_->group_by_columns = columns;
    return *this;
} 

SelectQueryBuilder& SelectQueryBuilder::having(const Expression& expression){
    ir_->having_clause = expression;
    return *this;
}

SelectQueryBuilder& SelectQueryBuilder::order_by(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs){
    ir_->order_by_columns = column_dirs;
    return *this;
} 

std::string SelectQueryBuilder::build() const {
    auto sql = dialect_->compile_select(*ir_);
    std::cout << sql << std::endl;
    return sql;
}

void SelectQueryBuilder::reset() {
    ir_->reset();
}

}
