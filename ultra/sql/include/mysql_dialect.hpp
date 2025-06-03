#ifndef QUICK_ULTRA_MYSQL_DIALECT_HPP
#define QUICK_ULTRA_MYSQL_DIALECT_HPP
#include "sql_dialect.hpp"
namespace quick{
namespace ultra{
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
};
}}// namespace quick::ultra
#endif