#ifndef QUICK_ULTRA_LINK_HPP
#define QUICK_ULTRA_LINK_HPP

#include <string>
namespace quick {
namespace ultra {
namespace sqljke {
struct Link{
	std::string column;
	std::string foreign_table;
	std::string foreign_column;
};
}}} //namespace quick::ultra::sql

#endif
