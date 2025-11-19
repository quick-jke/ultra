#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models/one_to_one.hpp"



int main() {
    //init driver
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect(quick::ultra::to_connection_string("localhost", "root", "rootjke7423", one_to_one::DATABASE_NAME));
    //init session
    quick::ultra::Session session(driver);

    //creating tables from generated file
    session.create_tables(one_to_one::TABLES);

    // auto Pass1 = std::make_shared<one_to_many::Passport>();
    // Pass1->set_num(5);
    // session.save(Pass1);


    auto u1 = std::make_shared<one_to_one::User>();
    u1->set_age(24);
    u1->set_degree(4.2);
    u1->set_is(true);
    u1->set_name("stepan");

    auto u2 = std::make_shared<one_to_one::User>();
    u2->set_age(34);
    u2->set_degree(4.7);
    u2->set_is(false);
    u2->set_name("antonuy");

    session.save(u1);
    session.save(u2);


    auto sql = session.select(one_to_one::User::COLUMNS)
        .from(one_to_one::User::TABLE_NAME)
        .where(one_to_one::User::age_equal(24))
        .build();

    std::cout << session.execute(sql)->debug(one_to_one::User::COLUMNS);
    
    
    return 0;
}



// TODO: CREATE TABLE (create_table/s)
// TODO: INSERT INTO (save, insert_into)
// TODO: SELECT (select, get_by_id, get_all)
// TODO: UPDATE

