#ifndef QUICK_ULTRA_SQL_INCLUDE_CREATE_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_CREATE_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include "column.hpp"
#include "create_table_query_ir.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
namespace quick::ultra::sqljke{
class CreateTableQueryBuilder : public SQLQueryBuilder {
public:
    explicit CreateTableQueryBuilder(const ISQLDialect* dialect) {
        dialect_ = dialect;
        ir_ = new CreateTableIR();
        ir_->if_not_exists_ = false;
    }

    void set_table_name(const std::string& table_name);

    CreateTableQueryBuilder& set_if_not_exists(bool enable = true);

    CreateTableQueryBuilder& add_column(const Column& column);

    CreateTableQueryBuilder& add_foreign_key(Link link);

    std::vector<std::string> build() const;

private:
    const ISQLDialect* dialect_;
    CreateTableIR* ir_;
};
}
#endif
