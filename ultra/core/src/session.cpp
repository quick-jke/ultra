#include "session.hpp"
#include "session_helper.hpp"

namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver) : driver_(driver) {
    scanner_ = HeaderScanner();
    sqlbuilder_ = SQLBuilder();
}

void Session::create_tables() {
    auto [tables, deps] = scanner_.getTablesAndDependencies();

    std::vector<std::string> requests;

    for(auto table : tables){
        requests.push_back(sqlbuilder_.sqlCreateTable(table));
    }


    for(auto dep : deps){
        requests.push_back(sqlbuilder_.sqlCreateDependency(dep));
    }
    
    if (requests.empty()) {
        std::cout << "No tables to create.\n";
        return;
    }


    driver_->begin_transaction();

    try {
        for (const auto& req : requests) {
            std::cout << req << std::endl;
            // driver_->execute(req);
        }
        driver_->commit();
    } catch (const std::exception& e) {
        driver_->rollback();
        std::cerr << "Error creating tables: " << e.what() << std::endl;
        throw;
    }
}



}    
}