#ifndef CORE_DRIVER_HPP
#define CORE_DRIVER_HPP

#include "idriver.hpp"
#include "class_metadata.hpp"
#include "sql_builder.hpp"
#include "scanner.hpp"

namespace quick{
namespace ultra{

class Session{
public:
    Session(std::shared_ptr<IDriver> driver);

    void create_tables();



private:
    std::shared_ptr<IDriver> driver_;

};



}
}


#endif