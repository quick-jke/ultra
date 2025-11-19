#include "select_query_builder.hpp"
#include <iostream>
namespace quick::ultra::sqljke{

SelectQueryBuilder::SelectQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect) {}

void SelectQueryBuilder::set_columns(const std::vector<sqljke::Column>& columns){
    columns_ = columns;
}

SelectQueryBuilder& SelectQueryBuilder::from(Table table) {
    table_name_ = dialect_->quote_identifier(table.get());
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

std::string SelectQueryBuilder::build() {
    std::ostringstream oss;
    oss << "SELECT ";

    if (columns_.empty()) {
        oss << "*";
    } else {
        for (size_t i = 0; i < columns_.size(); ++i) {
            if (i > 0) oss << ", ";
            Column col = columns_.at(i);
            oss << dialect_->quote_identifier(col.get());
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

    if (limit_ > 0) {
        oss << " " << dialect_->limit_clause(limit_, offset_);
    }
    std::cout << oss.str() << std::endl;
    query_ = oss.str();
    return oss.str();
}

std::string SelectQueryBuilder::query(){
    return query_;
}



}
