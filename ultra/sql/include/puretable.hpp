#ifndef QUICK_ULTRA_PURE_TABLE_HPP
#define QUICK_ULTRA_PURE_TABLE_HPP

#include <string>
#include <vector> 
#include "link.hpp"
#include "column.hpp"
namespace quick {
namespace ultra {
namespace sqljke {
struct PureTable{
	std::string name_;
	std::vector<Column> columns_;
	std::vector<Link> links_;

    PureTable(const PureTable&) = default;
    PureTable(PureTable&&) = default;
    PureTable& operator=(const PureTable&) = default;
    PureTable& operator=(PureTable&&) = default;
    PureTable(const std::string& name, std::vector<Column> columns, std::vector<Link> links) {
        name_ = name;
        columns_ = columns;
        links_ = links;
    }
};
}}} //namespace quick::ultra::sql

#endif
