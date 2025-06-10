#ifndef QUICK_ULTRA_SQL_SELECT_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_SELECT_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <variant>
namespace quick{
namespace ultra{
namespace sqljke {

struct SelectQuery{
    std::vector<std::string> columns;
    std::string table_name;
    std::string where;
    std::variant<int, std::pair<int, int>> limit;
};

class SelectQueryBuilder : public SQLQueryBuilder {
public:
    SelectQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect) {}

    // SelectQueryBuilder& select(const std::vector<std::string>& columns) {
    //     columns_ = columns;
    //     return *this;
    // }

    SelectQueryBuilder& from(const std::string& table) {
        table_ = dialect_->quote_identifier(table);
        return *this;
    }

    SelectQueryBuilder& where(const std::string& condition) {
        where_clause_ = condition;
        return *this;
    }

    SelectQueryBuilder& limit(int limit, int offset = 0) {
        limit_ = limit;
        offset_ = offset;
        return *this;
    }

    std::string build() const {
        std::ostringstream oss;
        oss << "SELECT ";

        if (columns_.empty()) {
            oss << "*";
        } else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << dialect_->quote_identifier(columns_[i]);
            }
        }

        oss << " FROM " << table_;

        if (!where_clause_.empty()) {
            oss << " WHERE " << where_clause_;
        }

        if (limit_ > 0) {
            oss << " " << dialect_->limit_clause(limit_, offset_);
        }

        return oss.str();
    }

    void set_columns(const std::vector<std::string>& columns){
        columns_ = columns;
    }

private:
    const ISQLDialect* dialect_;
    std::vector<std::string> columns_;
    std::string table_;
    std::string where_clause_;
    int limit_ = -1;
    int offset_ = 0;
};
}}}// namespace quick::ultra::sql
#endif

/*

auto query = std::make_unique<SelectQueryBuilder>(dialect.get());

query->select({"id", "name", "email"})
        ->from("users")
        ->where("age > 30 AND status = 'active'")
        ->limit(10, 5)
        ->build();

driver_->execute(query);
*/
