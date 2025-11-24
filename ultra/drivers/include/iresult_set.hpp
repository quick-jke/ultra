#ifndef DRIVER_RESULT_SET_HPP
#define DRIVER_RESULT_SET_HPP
#include <string>
#include <memory>
#include <vector> 
#include <unordered_map>
#include "column.hpp"
namespace quick::ultra {
using Objects = std::vector<std::unordered_map<std::string, std::string>>;
class ResultSet {
public:
    virtual ~ResultSet() = default;

    virtual bool next() = 0; 
    virtual int get_int(const std::string& column) = 0;
    virtual std::string get_string(const std::string& column) = 0;
    virtual bool get_bool(const std::string& column) = 0;
    virtual double get_double(const std::string& column) = 0;
    virtual char get_char(const std::string& column) = 0;
    virtual std::string debug() = 0;
    virtual Objects to_vector_of_maps() = 0;
};
using ResultSetPtr = std::unique_ptr<ResultSet>;
}// namespace quick::ultra
#endif
