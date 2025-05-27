#ifndef CORE_DRIVER_HPP
#define CORE_DRIVER_HPP

#include "idriver.hpp"
#include "sql_builder.hpp"
#include "scanner.hpp"


// #include "generated/session_helper.hpp"


namespace quick{
namespace ultra{

class Session{
public:
    Session(std::shared_ptr<IDriver> driver);
    void create_tables();

    template<typename T>
    void save(const T& obj);

private:
    std::shared_ptr<IDriver> driver_;
    HeaderScanner scanner_;
    SQLBuilder sqlbuilder_;
};



}
}


#endif