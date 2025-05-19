#include "session.hpp"

namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver) : driver_(driver) {
    scanner_ = HeaderScanner();
    sqlbuilder_ = SQLBuilder();
}

void Session::create_tables(){
    auto requests = sqlbuilder_.getSqlByEntities(scanner_.getTables().value());
    for(auto req : requests){
        // driver_->execute(req);
        std::cout << req << std::endl;
    }
}

}    
}