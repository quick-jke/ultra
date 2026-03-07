#include "delete_query_builder.hpp"

namespace quick::ultra::sqljke{

DeleteQueryBuilder& DeleteQueryBuilder::set_table(Table table) {
    table_name_ = dialect_->quote_table(table);
    return *this;
}

DeleteQueryBuilder& DeleteQueryBuilder::where(const Expression& expression) {
    where_clauses_.push_back(expression.get());
    return *this;
}

std::string DeleteQueryBuilder::build() {
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

}
