#ifndef QUICK_ULTRA_SQL_INTERFACE_IDIALECT_HPP
#define QUICK_ULTRA_SQL_INTERFACE_IDIALECT_HPP
#include <string>
#include <vector>
#include <optional>
#include <utility>
#include "expr.hpp"
#include "type.hpp"
#include "column.hpp"
#include "order_dir.hpp"
#include "table.hpp"
#include "aggregate.hpp"
#include "scalar.hpp"
#include "select_query_ir.hpp"
#include "update_query_ir.hpp"
namespace quick{
namespace ultra{
namespace sqljke {




class ISQLDialect {
public:
    virtual std::string scalar_clause(Scalar scalar) const = 0; 
    virtual std::string aggregate_clause(Aggregate aggregate) const = 0;
    virtual std::string order_by_clause(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs) const = 0;
    virtual std::string group_by_clause(std::vector<Column> columns) const = 0;
    virtual std::string having_clause(Expression expression) const = 0;
    virtual std::string quote_table(const Table& table) const = 0;
    virtual std::string quote_column(const Column& column) const = 0;
    virtual std::string where_clause(Expression expr) const = 0;
    virtual std::string limit_clause(int limit, int offset = 0) const = 0;
    virtual std::string auto_increment_clause() const = 0;
    virtual std::string if_not_exists_clause() const = 0;
    virtual std::string type_clause(TYPE t) const = 0;
    virtual std::string compile_select(const SelectQueryIR& ir) const = 0;
    virtual std::string compile_insert() const = 0;
    virtual std::string compile_drop() const = 0;
    virtual std::string compile_update(const UpdateQueryIR& ir) const = 0;
    virtual ~ISQLDialect() = default;
    
};
}}}// namespace quick::ultra::sql
#endif
