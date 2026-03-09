#ifndef ULTRA_SQL_INCLUDE_INSERT_QUERY_IR_HPP
#define ULTRA_SQL_INCLUDE_INSERT_QUERY_IR_HPP

#include <string>
#include <vector>

namespace quick::ultra::sqljke{

struct InsertQueryIR{
    std::string table_name_;
    std::vector<std::string> columns_;
    std::vector<std::string> values_;

    InsertQueryIR(){reset();}

    void reset(){

    }
};
}
#endif
