#ifndef QUICK_ULTRA_SQL_INCLUDE_MYSQL_DIALECT_HPP
#define QUICK_ULTRA_SQL_INCLUDE_MYSQL_DIALECT_HPP
#include "sql_dialect.hpp"
#include "type.hpp"
#include "sign.hpp"
#include <sstream>
namespace quick::ultra::sqljke {
class MySQLDialect : public ISQLDialect {
public:

    std::string read_expression(Expression expr) const{
        switch (expr.sign()) {
            case SIGN::MORE_THAN: return " > "; 
            case SIGN::LESS_THAN: return " < "; 
            case SIGN::MORE_OR_EQUAL: return " >= "; 
            case SIGN::LESS_OR_EQUAL: return " <= "; 
            case SIGN::EQUAL: return " = "; 
            case SIGN::NOT_EQUAL: return " != "; 
            default: return ""; 
        }
    }

    std::string quote_table(const Table& table) const override {
        return "`" + table.get() + "`";
    }

    std::string quote_column(const Column& column) const override {
        return "`" + column.get() + "`";
    }

    std::string limit_clause(int limit, int offset = 0) const override {
        if (offset == 0) {
            return "LIMIT " + std::to_string(limit);
        } else {
            return "LIMIT " + std::to_string(offset) + ", " + std::to_string(limit);
        }
    }

    std::string type_clause(TYPE t) const override{
        switch (t)
        {
        case TYPE::STRING:{
            return "VARCHAR(255)";
        }
        case TYPE::INT:{
            return "INT";
        }
        case TYPE::BIGINT:{
            return "BIGINT";
        }
        case TYPE::SMALLINT:{
            return "SMALLINT";
        }
        case TYPE::TINYINT:{
            return "TINYINT";
        }
        case TYPE::DECIMAL:{
            return "DECIMAL";
        }
        case TYPE::FLOAT:{
            return "FLOAT";
        }
        case TYPE::DOUBLE:{
            return "DOUBLE";
        }    
        case TYPE::VARCHAR:{
            return "VARCHAR(255)";
        }    
        case TYPE::BOOL:{
            return "BOOL";
        }
        default:
            return "UNKNOWN";
        }
    }

    std::string auto_increment_clause() const {
        return "AUTO_INCREMENT";
    }

    std::string if_not_exists_clause() const {
        return "IF NOT EXISTS";
    }

    std::string order_by_clause(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs) const {
        std::stringstream oss;
        oss << "ORDER BY ";
        for(size_t i = 0; i < column_dirs.size(); ++i){
            if (i > 0) {
                oss << ", ";
            }
            oss << column_dirs.at(i).first.name() << "  " << order_dir_to_string(column_dirs.at(i).second);
        }
        return oss.str();
    }

    std::string group_by_clause(std::vector<Column> columns) const override {
        if (columns.empty()) {
            return "";
        }

        std::ostringstream oss;
        oss << "GROUP BY ";
        for (size_t i = 0; i < columns.size(); ++i) {
            if (i > 0) {
                oss << ", ";
            }
            oss << quote_column(columns[i].get());  
        }
        return oss.str();
    }
    
    std::string having_clause(Expression expression) const {
        return "HAVING " + expression.get();
    }

    std::string where_clause(Expression expression) const {
        return expression.get();
    }

    std::string aggregate_clause(Aggregate aggregate) const override{
        return aggregate.to_string();
    }

    std::string scalar_clause(Scalar scalar) const override{
        return scalar.to_string();
    }

    std::string compile_select(const SelectQueryIR& ir) const override {
        std::ostringstream oss;
        oss << "SELECT ";

        if (!ir.select_list.empty()) {
            for (size_t i = 0; i < ir.select_list.size(); ++i) {
                if (i > 0) oss << ", ";
                std::visit([&oss, this](auto item) {
                    using T = std::decay_t<decltype(item)>;
                    if constexpr (std::is_same_v<T, Column>) {
                        oss << quote_column(item);
                    } else if constexpr (std::is_same_v<T, Aggregate>) {
                        oss << aggregate_clause(item);
                    } else if constexpr (std::is_same_v<T, Scalar>) {
                        oss << scalar_clause(item);
                    }
                }, ir.select_list[i]);
            }
        } else {
            oss << "*";
        }
        
        oss << " FROM " << quote_table(*ir.table);

        if (!ir.where_clauses.empty()) {
            oss << " WHERE ";
            for (size_t i = 0; i < ir.where_clauses.size(); ++i) {
                if (i > 0) oss << " AND ";
                oss << where_clause(ir.where_clauses[i]);
            }
        }

        if (ir.group_by_columns.has_value()) {
            oss << " " << group_by_clause(ir.group_by_columns.value());
        }

        if (ir.having_clause.has_value()) {
            oss << " HAVING " << having_clause(ir.having_clause.value());
        }

        if (ir.order_by_columns.has_value()) {
            oss << " " << order_by_clause(ir.order_by_columns.value());
        }

        if (ir.limit_offset.has_value() && ir.limit_offset->first > 0) {
            oss << " " << limit_clause(ir.limit_offset->first, ir.limit_offset->second);
        }
        
        return oss.str();
    }


    std::string compile_insert() const {
        return "";
    }
    std::string compile_drop() const {
        return "";
    }
    std::string compile_update(const UpdateQueryIR& ir) const override {
        if (ir.table == nullptr) {
            throw std::runtime_error("Table is not set in UPDATE query");
        }

        if (ir.column_value_map.empty()) {
            throw std::runtime_error("No columns to update in UPDATE query");
        }

        std::ostringstream oss;
        
        oss << "UPDATE " << quote_table(*ir.table) << " SET ";

        bool first = true;
        for (const auto& [column_ptr, value] : ir.column_value_map) {
            if (column_ptr == nullptr) {
                continue; 
            }
            
            if (!first) {
                oss << ", ";
            }
            oss << quote_column(*column_ptr) << " = '" << value << "'";
            first = false;
        }

        if (!ir.where_clauses.empty()) {
            oss << " WHERE ";
            for (size_t i = 0; i < ir.where_clauses.size(); ++i) {
                if (i > 0) oss << " AND ";
                oss << this->where_clause(ir.where_clauses[i]);
            }
        }

        oss << ";";
        return oss.str();
    }


    std::vector<std::string> compile_create_table(const CreateTableIR& ir) const {
        std::vector<std::string> queries;

        for (const auto& table : ir.tables) {
            std::ostringstream oss;
            oss << "CREATE TABLE ";

            if (ir.if_not_exists_) {
                oss << if_not_exists_clause() << " ";
            }

            oss << quote_table(table.name) << " (\n";

            for (size_t i = 0; i < table.columns.size(); ++i) {
                auto col = table.columns[i];
                if (i > 0) oss << ",\n";
                oss << "  " << quote_column(col.name()) << " " << type_clause(col.type());

                if (!col.is_nullable()) oss << " NOT NULL";
                if (col.is_primary_key()) oss << " PRIMARY KEY";
                if (col.is_unique()) oss << " UNIQUE";
                if (col.is_auto_increment()) oss << " " << auto_increment_clause();
                
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
                oss << ",\n  FOREIGN KEY (" << quote_column(fk.column) << ")"
                    << " REFERENCES " << quote_table(fk.foreign_table)
                    << " (" << quote_column(fk.foreign_column) << ")";
            }

            oss << "\n);"; 
            queries.push_back(oss.str());
        }

        return queries;
    }
};
}
#endif

