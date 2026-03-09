#ifndef QUICK_ULTRA_SQL_INCLUDE_SELECT_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INCLUDE_SELECT_QUERY_BUILDER_HPP
#include "sql_query_builder.hpp"
#include "sql_dialect.hpp"
#include "table.hpp"
#include "order_dir.hpp"
#include "aggregate.hpp"
#include "scalar.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <variant>
namespace quick::ultra::sqljke {

class SelectQueryBuilder : public SQLQueryBuilder {
public:
    explicit SelectQueryBuilder(const ISQLDialect* dialect) {
        dialect_ = dialect;
        ir_ = new SelectQueryIR();
    }

    void set_select_list(const std::vector<std::variant<Column, Aggregate, Scalar>> select_list);

    SelectQueryBuilder& from(const Table& table);

    SelectQueryBuilder& where(const Expression& expression);

    SelectQueryBuilder& group_by(const std::vector<Column>& columns); 

    SelectQueryBuilder& having(const Expression& expression);

    SelectQueryBuilder& order_by(const std::vector<std::pair<Column, ORDER_DIR>>& column_dirs); 

    SelectQueryBuilder& limit(int limit, int offset = 0);

    std::string build() const;

    void reset();

private:
    const ISQLDialect* dialect_;
    SelectQueryIR* ir_;
};
}
#endif

