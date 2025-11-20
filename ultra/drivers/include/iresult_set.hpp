#ifndef DRIVER_RESULT_SET_HPP
#define DRIVER_RESULT_SET_HPP
#include <string>
#include <memory>
#include <vector> 
#include "column.hpp"
namespace quick::ultra {
class ResultSet {
public:
    virtual ~ResultSet() = default;

    virtual bool next() = 0; 
    virtual int get_int(const std::string& column) = 0;
    virtual std::string get_string(const std::string& column) = 0;
    virtual bool get_bool(const std::string& column) = 0;
    virtual double get_double(const std::string& column) = 0;
    virtual char get_char(const std::string& column) = 0;
    virtual std::string debug(std::vector<sqljke::Column> columns) = 0;
};
using ResultSetPtr = std::unique_ptr<ResultSet>;
}// namespace quick::ultra
#endif
