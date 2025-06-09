#ifndef QUICK_ULTRA_SQL_RELATION_HPP
#define QUICK_ULTRA_SQL_RELATION_HPP
#include <memory>
#include "table.hpp"
namespace quick {
namespace ultra {
namespace sqljke {
struct IRelation{
public:
};
struct OneToOneRelation : public IRelation {
	std::shared_ptr<SQLTable> first_;
	std::shared_ptr<SQLTable> second_;
};
struct OneToManyRelation : public IRelation {
	std::shared_ptr<SQLTable> one_;
	std::shared_ptr<SQLTable> many_;
};
struct ManyToOneRelation : public IRelation {
	std::shared_ptr<SQLTable> many_;
	std::shared_ptr<SQLTable> one_;
};
struct ManyToManyRelation : public IRelation {
	std::shared_ptr<SQLTable> first_;
	std::shared_ptr<SQLTable> second_;
};
}}} //namespace quick::ultra::sql
#endif
