#ifndef QUICK_ULTRA_SQL_INSERT_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INSERT_QUERY_BUILDER_HPP

#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include <string>
#include <sstream>
#include <vector>

namespace quick {
namespace ultra {
namespace sqljke {

class InsertQueryBuilder : public SQLQueryBuilder {
public:
    explicit InsertQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect) {}


    InsertQueryBuilder& set_table(const std::string& table_name){
        table_name_ = dialect_->quote_identifier(table_name);
        return *this;
    }

    InsertQueryBuilder& columns(const std::vector<std::string>& columns) {
        columns_ = columns;
        return *this;
    }

    InsertQueryBuilder& values(const std::vector<std::string>& values) {
        values_ = values;
        return *this;
    }

    std::string build() const {
        std::ostringstream oss;
        oss << "INSERT INTO " << table_name_ << " ";

        if (columns_.empty()) {
            throw std::runtime_error("Columns must be specified for INSERT");
        }

        oss << "("; 
        for (size_t i = 0; i < columns_.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << dialect_->quote_identifier(columns_[i]);
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

private:
    const ISQLDialect* dialect_;
    std::string table_name_;
    std::vector<std::string> columns_;
    std::vector<std::string> values_;

    bool is_string_value(const std::string& val) const {
        return !val.empty() && val[0] != '\'' && val.find_first_of("0123456789") == std::string::npos;
    }
};

}}} // namespace quick::ultra

#endif
