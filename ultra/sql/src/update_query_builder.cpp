#include "update_query_builder.hpp"
#include <iostream>

namespace quick::ultra::sqljke{

UpdateQueryBuilder& UpdateQueryBuilder::set_table(const Table& table){
    ir_->table = &table;
    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::set(const std::vector<Column>& columns, const std::vector<std::string>& values) {
    if (columns.size() != values.size()) {
        throw std::invalid_argument("Columns and values must have the same size");
    }

    for (size_t i = 0; i < columns.size(); ++i) {
        ir_->column_value_map[&columns[i]] = values[i];
    }

    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::set(const Column& column, std::variant<std::string, int, double, bool> value) {
    ir_->column_value_map[&column] = value;
    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::where(const Expression& expression) {
    ir_->where_clauses.push_back(expression);
    return *this;
}

std::string UpdateQueryBuilder::build() const {
    auto sql = dialect_->compile_update(*ir_);
    std::cout << sql << std::endl;
    return sql;
}

void UpdateQueryBuilder::reset() {
    ir_->reset();
}

}
