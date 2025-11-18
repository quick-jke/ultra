#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models/one_to_many.hpp"



int main() {
    //init driver
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect(quick::ultra::to_connection_string("localhost", "root", "rootjke7423", one_to_many::DATABASE_NAME));
    //init session
    quick::ultra::Session session(driver);

    //creating tables from generated file
    session.create_tables(one_to_many::tables);

    // auto Pass1 = std::make_shared<one_to_many::Passport>();
    // Pass1->set_num(5);
    // session.save(Pass1);


    auto passwords = session.get_all<one_to_many::Passport>();

    for(auto pass : passwords){
        std::cout << "id: " << pass->id() << " num: " << pass->num() << std::endl;
    }
    
    
    
    return 0;
}



// TODO: CREATE TABLE (create_table/s)
// TODO: INSERT INTO (save, insert_into)
// TODO: SELECT (select, get_by_id, get_all)
// TODO: UPDATE

