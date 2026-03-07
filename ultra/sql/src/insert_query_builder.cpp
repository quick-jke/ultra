#include "insert_query_builder.hpp"

namespace quick::ultra::sqljke{

InsertQueryBuilder& InsertQueryBuilder::set_table(const std::string& table_name){
    table_name_ = dialect_->quote_table(table_name);
    return *this;
}

InsertQueryBuilder& InsertQueryBuilder::columns(const std::vector<std::string>& columns) {
    columns_ = columns;
    return *this;
}

InsertQueryBuilder& InsertQueryBuilder::values(const std::vector<std::string>& values) {
    values_ = values;
    return *this;
}

std::string InsertQueryBuilder::build() const {
    std::ostringstream oss;
    oss << "INSERT INTO " << table_name_ << " ";

    if (columns_.empty()) {
        throw std::runtime_error("Columns must be specified for INSERT");
    }

    oss << "("; 
    for (size_t i = 0; i < columns_.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << dialect_->quote_column(columns_[i]);
    }
    oss << ") VALUES ";

    oss << "(";
    for (size_t i = 0; i < values_.size(); ++i) {
        if (i > 0) oss << ", ";

        const auto& val = values_[i];
        if (is_string_value(val)) {
            oss << "'" << val << "'";
        } else {
            oss << val;
        }
    }
    oss << ");";
    return oss.str();   
}

bool InsertQueryBuilder::is_string_value(const std::string& val) const {
    return !val.empty() && val[0] != '\'' && val.find_first_of("0123456789") == std::string::npos;
}

}
