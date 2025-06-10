#ifndef QUICK_ULTRA_SQL_CREATE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_CREATE_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include "column.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
namespace quick {
namespace ultra {
namespace sqljke{
struct TableDefinition {
    std::string name;
    std::vector<Column> columns;
    std::vector<std::tuple<std::string, std::string, std::string>> foreign_keys;
};
class CreateTableQueryBuilder : public SQLQueryBuilder {
public:
    explicit CreateTableQueryBuilder(const ISQLDialect* dialect)
        : dialect_(dialect), if_not_exists_(false) {}

    // CreateTableQueryBuilder& add_table(const std::string& table_name) {
    //     tables_.push_back({table_name, {}, {}});
    //     return *this;
    // }

    void set_table_name(const std::string& table_name){
        tables_.push_back({table_name, {}, {}});
    }

    CreateTableQueryBuilder& set_if_not_exists(bool enable = true) {
        if_not_exists_ = enable;
        return *this;
    }

    CreateTableQueryBuilder& add_column(const Column& column) {
        
        if (!tables_.empty() ) {
            if(column.type == "string"){ // FIXME: template 
                tables_.back().columns.push_back({column.name, "VARCHAR(255)", column.is_primary_key, column.is_auto_increment, column.is_nullable, column.default_value});
            }else{
                tables_.back().columns.push_back(column);
            }
            
        }
        return *this;
    }

    CreateTableQueryBuilder& add_foreign_key(const std::string& column, const std::string& foreign_table, const std::string& foreign_column) {
        if (!tables_.empty()) {
            tables_.back().foreign_keys.emplace_back(column, foreign_table, foreign_column);
        }
        return *this;
    }

    std::vector<std::string> build_all() const {
        std::vector<std::string> queries;

        for (const auto& table : tables_) {
            std::ostringstream oss;
            oss << "CREATE TABLE ";

            if (if_not_exists_) {
                oss << dialect_->if_not_exists_clause() << " ";
            }

            oss << dialect_->quote_identifier(table.name) << " (\n";

            for (size_t i = 0; i < table.columns.size(); ++i) {
                const auto& col = table.columns[i];
                if (i > 0) oss << ",\n";
                oss << "  " << dialect_->quote_identifier(col.name) << " " << col.type;

                if (!col.is_nullable) oss << " NOT NULL";
                if (col.is_primary_key) oss << " PRIMARY KEY";
                if (col.is_auto_increment) oss << " " << dialect_->auto_increment_clause();
                if (!col.default_value.empty()) {
                    oss << " DEFAULT ";
                    if (col.type == "INT" || col.type == "BIGINT" || col.type == "SMALLINT" ||
                        col.type == "TINYINT" || col.type == "DECIMAL" || col.type == "FLOAT" ||
                        col.type == "DOUBLE") {
                        oss << col.default_value;
                    } else {
                        oss << "'" << col.default_value << "'";
                    }
                }
            }

            for (const auto& fk : table.foreign_keys) {
                oss << ",\n  FOREIGN KEY (" << dialect_->quote_identifier(std::get<0>(fk)) << ")"
                    << " REFERENCES " << dialect_->quote_identifier(std::get<1>(fk))
                    << " (" << dialect_->quote_identifier(std::get<2>(fk)) << ")";
            }

            oss << "\n);"; 
            queries.push_back(oss.str());
        }

        return queries;
    }

private:
    const ISQLDialect* dialect_;
    std::vector<TableDefinition> tables_;
    bool if_not_exists_;
};
}}} // namespace quick::ultra::sql
#endif




/*
auto query = std::make_unique<CreateTableQueryBuilder>(dialect.get());

query->setIfNotExists()  
        ->addTable("users")
        ->addColumn(Column{"id", "INT", true, true, false, ""})
        ->addColumn(Column{"name", "VARCHAR(255)", false, false, true, "'default'"})
        ->build();

driver_->execute(query);
*/
