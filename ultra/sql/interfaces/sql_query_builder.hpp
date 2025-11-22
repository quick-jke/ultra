#ifndef QUICK_ULTRA_SQL_INTERFACE_IQUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_INTERFACE_IQUERY_BUILDER_HPP
#include <string>
#include <vector>
namespace quick{
namespace ultra{
namespace sqljke {
class SQLQueryBuilder {
public:
    // virtual std::vector<std::string> buildAll() const = 0;
    virtual ~SQLQueryBuilder() = default;
    // virtual std::string query();
};
}}}// namespace quick::ultra::sql
#endif
