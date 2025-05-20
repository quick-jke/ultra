#include "session.hpp"

namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver) : driver_(driver) {
    scanner_ = HeaderScanner();
    sqlbuilder_ = SQLBuilder();
}

void Session::create_tables() {
    auto tables = scanner_.getTables();

    

    if (!tables.has_value()) {
        throw std::runtime_error("Failed to scan tables");
    }

    auto requests = sqlbuilder_.getSqlByEntities(tables.value());

    if (requests.empty()) {
        std::cout << "No tables to create.\n";
        return;
    }

    driver_->begin_transaction();

    try {
        for (const auto& req : requests) {
            // std::cout << req << std::endl;
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