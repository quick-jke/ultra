#include "update_query_builder.hpp"

namespace quick::ultra::sqljke{

UpdateQueryBuilder& UpdateQueryBuilder::set_table(const Table& table){
    table_name_ = dialect_->quote_identifier(table);
    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::set(const std::vector<std::string>& columns, const std::vector<std::string>& values) {
    if (columns.size() != values.size()) {
        throw std::invalid_argument("Columns and values must have the same size");
    }

    for (size_t i = 0; i < columns.size(); ++i) {
        column_value_map_[columns[i]] = values[i];
    }

    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::set(const std::string& column, const std::string& value) {
    column_value_map_[column] = value;
    return *this;
}

UpdateQueryBuilder& UpdateQueryBuilder::add_column_value(std::pair<std::string, std::string> pair){
    column_value_map_.insert(pair);
    return *this;
}


UpdateQueryBuilder& UpdateQueryBuilder::where(const Expression& expression) {
    where_clauses_.push_back(expression.get());
    return *this;
}

std::string UpdateQueryBuilder::build() const {
    if (table_name_.empty()) {
        throw std::runtime_error("Table name is not set in UPDATE query");
    }

    std::ostringstream oss;
    oss << "UPDATE " << dialect_->quote_identifier(table_name_) << " SET ";

    bool first = true;
    for (const auto& [column, value] : column_value_map_) {
        if (!first) {
            oss << ", ";
        }
        oss << dialect_->quote_identifier(column) << " = '" << value << "'";
        first = false;
    }

    if (!where_clauses_.empty()) {
        oss << " WHERE ";
        for (size_t i = 0; i < where_clauses_.size(); ++i) {
            if (i > 0) oss << " AND ";
            oss << where_clauses_[i];
        }
    }

    oss << ";";
    return oss.str();
}

}
