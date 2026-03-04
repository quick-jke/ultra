#ifndef QUICK_ULTRA_SQL_INTERFACE_IDIALECT_HPP
#define QUICK_ULTRA_SQL_INTERFACE_IDIALECT_HPP
#include <string>
#include <vector>
#include <optional>
#include "expr.hpp"
#include "type.hpp"
#include "column.hpp"
#include "order_dir.hpp"
#include "table.hpp"
#include "aggregate.hpp"
#include "scalar.hpp"
namespace quick{
namespace ultra{
namespace sqljke {

struct SelectQueryIR {
    std::vector<std::variant<Column, Aggregate, Scalar>> select_list;
    std::string table_name; 
    std::vector<std::string> where_clauses;
    std::string group_by_columns;
    std::string order_by_columns;
    std::optional<std::pair<int, int>> limit_offset; 
    std::optional<std::string> having_clause;
};


class ISQLDialect {
public:
    virtual std::string scalar_clause(Scalar scalar) const = 0; 
    virtual std::string aggregate_clause(Aggregate aggregate) const = 0;
    virtual std::string order_by_clause(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs) const = 0;
    virtual std::string group_by_clause(std::vector<Column> columns) const = 0;
    virtual std::string having_clause(Expression expression) const = 0;
    virtual std::string quote_identifier(Table table) const = 0;
    virtual std::string where_clause(Expression expr) const = 0;
    virtual std::string limit_clause(int limit, int offset = 0) const = 0;
    virtual std::string auto_increment_clause() const = 0;
    virtual std::string if_not_exists_clause() const = 0;
    virtual std::string type_clause(TYPE t) const = 0;
    virtual std::string compile_select(const SelectQueryIR& ir) const = 0;
    virtual ~ISQLDialect() = default;
    
};
}}}// namespace quick::ultra::sql
#endif
