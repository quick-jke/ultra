#include "session.hpp"

namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver) : driver_(driver) {}

void Session::create_tables(){
    HeaderScanner scanner;
    SQLBuilder sql;
    // sql.createTables(scanner.getTables().value());
    driver_->execute(sql.createTables(scanner.getTables().value()));
    // driver_->execute()
}

}    
}