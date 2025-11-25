#include "select_query_builder.hpp"
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
    std::ostringstream oss;
    oss << "SELECT ";

    if (!select_list_.empty()) {
        for (size_t i = 0; i < select_list_.size(); ++i) {
            if (i > 0) oss << ", ";

            std::visit([&oss, this](auto item) {
                using T = std::decay_t<decltype(item)>;

                if constexpr (std::is_same_v<T, Column>) {
                    oss << dialect_->quote_identifier(item.get());
                } else if constexpr (std::is_same_v<T, Aggregate>) {
                    oss << dialect_->aggregate_clause(item);
                } else if constexpr (std::is_same_v<T, Scalar>) {
                    oss << dialect_->scalar_clause(item);
                }
            }, select_list_[i]);
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
