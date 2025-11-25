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

    std::string quote_identifier(Table table) const override {
        return "`" + table.get() + "`";
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
        case STRING:{
            return "VARCHAR(255)";
        }
        case INT:{
            return "INT";
        }
        case BIGINT:{
            return "BIGINT";
        }
        case SMALLINT:{
            return "SMALLINT";
        }
        case TINYINT:{
            return "TINYINT";
        }
        case DECIMAL:{
            return "DECIMAL";
        }
        case FLOAT:{
            return "FLOAT";
        }
        case DOUBLE:{
            return "DOUBLE";
        }    
        case VARCHAR:{
            return "VARCHAR(255)";
        }    
        case BOOL:{
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
            oss << column_dirs.at(i).first.name << "  " << order_dir_to_string(column_dirs.at(i).second);
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
            oss << quote_identifier(columns[i].get());  
        }
        return oss.str();
    }
    std::string having_clause(Expression expression) const {
        return "HAVING " + expression.get();
    }

    std::string where_clause(Expression expression) const {
        std::stringstream oss;
        oss << expression.field() << read_expression(expression);
        return oss.str();
    }

    std::string aggregate_clause(Aggregate aggregate) const override{
        return aggregate.to_string();
    }

    std::string scalar_clause(Scalar scalar) const override{
        return scalar.to_string();
    }



};
}// namespace quick::ultra::sql
#endif

/*
    MORE_THAN,
    LESS_THAN,
    MORE_OR_EQUAL,
    LESS_OR_EQUAL,
    EQUAL,
    NOT_EQUAL,

    LIKE,

    IS_TRUE,
    IS_FALSE,

    IS_NULL,
    IS_NOT_NULL
*/
