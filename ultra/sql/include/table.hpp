#ifndef QUICK_ULTRA_SQL_TABLE_HPP
#define QUICK_ULTRA_SQL_TABLE_HPP
#include <vector>
#include <string>
#include "column.hpp"
#include "link.hpp"
namespace quick{
namespace ultra{
namespace sqljke {
class SQLTable{
public:
	SQLTable() = default;
    virtual int id() const = 0;
	virtual std::string table_name() const = 0;
	virtual std::vector<quick::ultra::sqljke::Column> columns() const = 0;
	virtual std::vector<quick::ultra::sqljke::Link> links() const = 0;
	virtual std::vector<std::string> values() const = 0;
    virtual std::vector<std::string> column_names() const = 0;
	virtual ~SQLTable() = default;
};
}}} //namespace quick::ultra::sql
#endif
