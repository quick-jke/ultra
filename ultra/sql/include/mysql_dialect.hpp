#ifndef QUICK_ULTRA_MYSQL_DIALECT_HPP
#define QUICK_ULTRA_MYSQL_DIALECT_HPP
#include "sql_dialect.hpp"
#include <sstream>
namespace quick{
namespace ultra{
namespace sqljke {
class MySQLDialect : public ISQLDialect {
public:
    std::string quote_identifier(const std::string& name) const override {
        return "`" + name + "`";
    }

    std::string limit_clause(int limit, int offset = 0) const override {
        if (offset == 0) {
            return "LIMIT " + std::to_string(limit);
        } else {
            return "LIMIT " + std::to_string(offset) + ", " + std::to_string(limit);
        }
    }

    std::string auto_increment_clause() const {
        return "AUTO_INCREMENT";
    }

    std::string if_not_exists_clause() const {
        return "IF NOT EXISTS";
    }

    std::string where_clause(const ExprStruct& expr) const {
        std::stringstream oss;
        oss << expr.field_;
        switch (expr.expr_)
        {
        case MORE_THAN:{
            oss << " > ";
            break;
        }
        case LESS_THAN:{
            oss << " < ";
            break;
        }
        case MORE_OR_EQUAL:{
            oss << " >= ";
            break;
        }
        case LESS_OR_EQUAL:{
            oss << " <= ";
            break;
        }
        case EQUAL:{
            oss << " = ";
            break;
        }
        case NOT_EQUAL:{
            oss << " != ";
            break;
        }
        case LIKE:{

            break;
        }
        
        default:
            break;
        }
        return oss.str();
    }

};
}}}// namespace quick::ultra::sql
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
