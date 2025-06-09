#ifndef QUICK_ULTRA_SQL_IDIALECT_HPP
#define QUICK_ULTRA_SQL_IDIALECT_HPP
#include <string>
namespace quick{
namespace ultra{
namespace sqljke {
class ISQLDialect {
public:
    virtual std::string quote_identifier(const std::string& name) const = 0;
    virtual std::string limit_clause(int limit, int offset = 0) const = 0;
    virtual std::string auto_increment_clause() const = 0;
    virtual std::string if_not_exists_clause() const = 0;
    virtual ~ISQLDialect() = default;
};
}}}// namespace quick::ultra::sql
#endif
