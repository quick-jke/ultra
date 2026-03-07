#include "update_query_builder.hpp"
#include <iostream>

namespace quick::ultra::sqljke{

UpdateQueryBuilder& UpdateQueryBuilder::set_table(const Table& table){
    table_ = &table;
    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::set(const std::vector<Column>& columns, const std::vector<std::string>& values) {
    if (columns.size() != values.size()) {
        throw std::invalid_argument("Columns and values must have the same size");
    }

    for (size_t i = 0; i < columns.size(); ++i) {
        column_value_map_[&columns[i]] = values[i];
    }

    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::set(const Column& column, const std::string& value) {
    column_value_map_[&column] = value;
    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::where(const Expression& expression) {
    where_clauses_.push_back(expression);
    return *this;
}

std::string UpdateQueryBuilder::build() const {

    UpdateQueryIR ir;
    ir.table = table_;
    ir.where_clauses = where_clauses_;
    ir.column_value_map = column_value_map_;

    auto sql = dialect_->compile_update(ir);

    std::cout << sql << std::endl;

    return sql;

}

void UpdateQueryBuilder::reset() {
    table_ = nullptr; 
    column_value_map_.clear(); 
    where_clauses_.clear(); 
}

}
