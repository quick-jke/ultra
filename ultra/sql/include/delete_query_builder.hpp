#ifndef QUICK_ULTRA_SQL_INCLUDE_DELETE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_DELETE_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"

namespace quick::ultra::sqljke {

class DeleteQueryBuilder : public SQLQueryBuilder {
public:
    explicit DeleteQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect) {}

    DeleteQueryBuilder& set_table(Table table)
    {
        table_name_ = dialect_->quote_identifier(table);
        return *this;
    }

    DeleteQueryBuilder& where(const Expression& expression)
    {
        where_clauses_.push_back(expression.get());
        return *this;
    }

    std::string build()
    {
        std::stringstream oss;

        oss << "DELETE FROM ";

        oss << table_name_;

        if (!where_clauses_.empty()) {
            oss << " WHERE ";
            for (size_t i = 0; i < where_clauses_.size(); ++i) {
                if (i > 0) oss << " AND ";
                oss << where_clauses_[i];
            }
        }

        return oss.str();
    }

private:
    const ISQLDialect* dialect_;
    std::string table_name_;
    std::vector<std::string> where_clauses_;

};

}

#endif
