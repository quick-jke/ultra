#ifndef QUICK_ULTRA_SQL_QUERY_BUILDER_HPP
#define QUICK_ULTRA_SQL_QUERY_BUILDER_HPP
#include <string>
#include <vector>
namespace quick{
namespace ultra{
namespace sqljke {
class SQLQueryBuilder {
public:
    // virtual std::vector<std::string> buildAll() const = 0;
    virtual ~SQLQueryBuilder() = default;
};
}}}// namespace quick::ultra::sql
#endif
