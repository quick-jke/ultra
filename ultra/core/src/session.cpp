#include "session.hpp"

namespace quick{
namespace ultra{

Session::Session(std::shared_ptr<IDriver> driver)
    : driver_(std::move(driver)) {

    switch (driver_->type()) {
        case DriverType::MySQL:
            dialect_ = std::make_unique<MySQLDialect>();
            break;
        default:
            dialect_ = nullptr;
            break;
    }

    create_tables();
}

void Session::create_tables() {
    auto builder = std::make_unique<CreateTableQueryBuilder>(dialect_.get());

    auto queries = builder->setIfNotExists()
                              .addTable("users")
                              .addColumn(Column{"id", "INT", true, true, false, ""})
                              .addColumn(Column{"name", "VARCHAR(255)", false, false, true, "'default'"})
                              .addColumn(Column{"age", "INT", false, false, false, "0"})
                              .addTable("wow")
                              .addColumn(Column{"id", "INT", true, true, false, ""})
                              .addColumn(Column{"email", "VARCHAR(255)", false, false, true, "'default'"})
                              .buildAll();

    for (const auto& sql : queries) {
        // std::cout << sql << std::endl;
        driver_->execute(sql); 
    }
}


//temp method
void Session::select(){
    auto query = std::make_unique<SelectQueryBuilder>(dialect_.get());

    auto sql = query->select({"id", "name", "age"})
            .from("users")
            .where("age > 30")
            .limit(2, 2)
            .build();

    std::cout << sql << std::endl;

    try{
        auto result = driver_->query(sql);
    
        if (!result) {
            std::cerr << "Query returned no result." << std::endl;
            return;
        }
    
        std::cout << "ID\tName\tAge\n";
    
        while (result->next()) {
            int id = result->get_int("id");
            std::string name = result->get_string("name");
            int age = result->get_int("age");
    
            std::cout << id << "\t" << name << "\t" << age << "\n";
        }
    }catch (const std::exception& e) {
        std::cerr << "Exception during query: " << e.what() << std::endl;
    }
}

//furure
void Session::insert_into() {
    // auto query = std::make_unique<InsertQueryBuilder>(dialect_.get());

    // std::string sql = builder->insert_into("users")
    //                           .columns({"name", "age"})
    //                           .values({"Alice", "35"})
    //                           .build();

    // driver_->execute(sql);
}

void Session::drop_table() {
    // auto query = std::make_unique<DropTableQueryBuilder>(dialect_.get());
    // std::string sql = builder->drop_table("users").if_exists().build();
    // driver_->execute(sql);
}




}}// namespace quick::ultra