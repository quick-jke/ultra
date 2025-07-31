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
    virtual const int id() const = 0;
    virtual void set_id(int id) = 0;
	virtual std::string table_name() const = 0;
	virtual std::vector<quick::ultra::sqljke::Column> columns() const = 0;
	virtual std::vector<quick::ultra::sqljke::Link> links() const = 0;
	virtual std::vector<std::string> values() const = 0;
    virtual std::vector<std::string> column_names() const = 0;
	virtual ~SQLTable() = default;

    virtual std::vector<std::shared_ptr<SQLTable>> get_dependent_objects() const {
        return {}; // по умолчанию — нет зависимостей
    }
};
}}} //namespace quick::ultra::sql
#endif
