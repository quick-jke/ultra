#ifndef DRIVER_RESULT_SET_HPP
#define DRIVER_RESULT_SET_HPP

#include <string>
#include <memory>

namespace quick {
namespace ultra {

class ResultSet {
public:
    virtual ~ResultSet() = default;

    virtual bool next() = 0; 
    virtual int get_int(const std::string& column) = 0;
    virtual std::string get_string(const std::string& column) = 0;
};

using ResultSetPtr = std::unique_ptr<ResultSet>;

} 
}

#endif