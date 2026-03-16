#ifndef QUICK_ULTRA_SQL_INCLUDE_MYSQL_DIALECT_HPP
#define QUICK_ULTRA_SQL_INCLUDE_MYSQL_DIALECT_HPP
#include "sql_dialect.hpp"
#include "type.hpp"
#include "sign.hpp"
#include <sstream>
#include <string>
namespace quick::ultra::sqljke {
class MySQLDialect : public ISQLDialect {
public:

    std::string read_expression(Expression expr) const;

    std::string quote_table(const Table& table) const override;

    std::string quote_column(const Column& column) const override;

    std::string limit_clause(int limit, int offset = 0) const override;

    std::string type_clause(TYPE t) const override;

    std::string auto_increment_clause() const;

    std::string if_not_exists_clause() const;

    std::string order_by_clause(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs) const;

    std::string group_by_clause(std::vector<Column> columns) const override;
    
    std::string having_clause(Expression expression) const;

    std::string where_clause(Expression expression) const;

    std::string aggregate_clause(Aggregate aggregate) const override;

    std::string scalar_clause(Scalar scalar) const override;

    std::string compile_select(const SelectQueryIR& ir) const override;

    std::string compile_insert() const;

    std::string compile_drop() const;

    std::string compile_update(const UpdateQueryIR& ir) const override;


    std::vector<std::string> compile_create_table(const CreateTableIR& ir) const;
};
}
#endif

