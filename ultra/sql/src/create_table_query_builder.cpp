#include "create_table_query_builder.hpp"

namespace quick::ultra::sqljke{

void CreateTableQueryBuilder::set_table_name(const std::string& table_name){
    tables_.push_back({table_name, {}, {}});
}

CreateTableQueryBuilder& CreateTableQueryBuilder::set_if_not_exists(bool enable) {
    if_not_exists_ = enable;
    return *this;
}

CreateTableQueryBuilder& CreateTableQueryBuilder::add_column(const Column& column) {
    if (!tables_.empty() ) {
        tables_.back().columns.push_back(column);
    }
    return *this;
}

CreateTableQueryBuilder& CreateTableQueryBuilder::add_foreign_key(Link link) {
    if (!tables_.empty()) {
        tables_.back().foreign_keys.emplace_back(link);
    }
    return *this;
}

std::vector<std::string> CreateTableQueryBuilder::build() const {
    std::vector<std::string> queries;

    for (const auto& table : tables_) {
        std::ostringstream oss;
        oss << "CREATE TABLE ";

        if (if_not_exists_) {
            oss << dialect_->if_not_exists_clause() << " ";
        }

        oss << dialect_->quote_table(table.name) << " (\n";

        for (size_t i = 0; i < table.columns.size(); ++i) {
            auto col = table.columns[i];
            if (i > 0) oss << ",\n";
            oss << "  " << dialect_->quote_column(col.name()) << " " << dialect_->type_clause(col.type());

            if (!col.is_nullable()) oss << " NOT NULL";
            if (col.is_primary_key()) oss << " PRIMARY KEY";
            if (col.is_unique()) oss << " UNIQUE";
            if (col.is_auto_increment()) oss << " " << dialect_->auto_increment_clause();
            
            if (!col.default_value().empty()) {
                oss << " DEFAULT ";
                switch(col.type()){
                    case TYPE::STRING:{
                        oss << "'" << col.default_value() << "'";
                        break;
                    }
                    default:{
                        oss << col.default_value();
                        break;
                    }
                }
            }
        }

        for (const auto& fk : table.foreign_keys) {
            oss << ",\n  FOREIGN KEY (" << dialect_->quote_column(fk.column) << ")"
                << " REFERENCES " << dialect_->quote_table(fk.foreign_table)
                << " (" << dialect_->quote_column(fk.foreign_column) << ")";
        }

        oss << "\n);"; 
        queries.push_back(oss.str());
    }

    return queries;
}

}
