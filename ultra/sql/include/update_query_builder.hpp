#ifndef QUICK_ULTRA_SQL_UPDATE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_UPDATE_QUERY_BUILDER_HPP
#include <map>
#include <string>
#include "utility"
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include <sstream>
namespace quick {
namespace ultra {
namespace sqljke{


class UpdateQueryBuilder : public SQLQueryBuilder{
public:
    explicit UpdateQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect){}

    UpdateQueryBuilder& set_table(const std::string& table_name){
        table_name_ = table_name;
        return *this;
    }

    UpdateQueryBuilder& set(const std::vector<std::string>& columns,
                                           const std::vector<std::string>& values) {
        if (columns.size() != values.size()) {
            throw std::invalid_argument("Columns and values must have the same size");
        }

        for (size_t i = 0; i < columns.size(); ++i) {
            column_value_map_[columns[i]] = values[i];
        }

        return *this;
    }
    
    UpdateQueryBuilder& set(const std::string& column, const std::string& value) {
        column_value_map_[column] = value;
        return *this;
    }

    UpdateQueryBuilder& add_column_value(std::pair<std::string, std::string> pair){
        column_value_map_.insert(pair);
        return *this;
    }
    

    UpdateQueryBuilder& where(const std::string& condition) {
        where_clause_ = condition;
        return *this;
    }

    std::string build() const {
        if (table_name_.empty()) {
            throw std::runtime_error("Table name is not set in UPDATE query");
        }

        std::ostringstream oss;
        oss << "UPDATE " << dialect_->quote_identifier(table_name_) << " SET ";

        // Генерируем SET часть
        bool first = true;
        for (const auto& [column, value] : column_value_map_) {
            if (!first) {
                oss << ", ";
            }
            oss << dialect_->quote_identifier(column) << " = '" << value << "'";
            first = false;
        }

        // Добавляем WHERE, если задано
        if (!where_clause_.empty()) {
            oss << " WHERE " << where_clause_;
        }

        oss << ";";
        return oss.str();
    }

private:
    const ISQLDialect* dialect_;
    std::string table_name_;
    std::map<std::string, std::string> column_value_map_;
    std::string where_clause_;
};


}}}


#endif
