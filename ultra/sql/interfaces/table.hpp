#ifndef QUICK_ULTRA_SQL_INTERFACE_TABLE_HPP
#define QUICK_ULTRA_SQL_INTERFACE_TABLE_HPP
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include "column.hpp"
#include "link.hpp"
namespace quick{
namespace ultra{
namespace sqljke {

class Table{
public:
    Table(const std::string name) : name_(name){}
    std::string get() const { return name_; }
private:
    std::string name_;
};

class SQLTable{
public:
	SQLTable()                                                                   = default;
	virtual ~SQLTable()                                                          = default;
    virtual const int id() const                                                 = 0;
    virtual void set_id(int id)                                                  = 0;
    virtual std::string table_name() const                                       = 0;
	virtual std::vector<Column> columns() const                                  = 0;
	virtual std::vector<Link> links() const                                      = 0;
	virtual std::vector<std::string> values() const                              = 0;
    virtual std::vector<std::string> column_names() const                        = 0;
    virtual std::vector<std::shared_ptr<SQLTable>> get_dependent_objects() const = 0;
};
}}} //namespace quick::ultra::sql
#endif
