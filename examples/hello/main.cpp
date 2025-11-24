#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models/one_to_one.hpp"



int main() {
    //init driver
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect(quick::ultra::to_connection_string("localhost", "root", "root7423", one_to_one::DATABASE_NAME));
    //init session
    quick::ultra::Session session(driver);

    //creating tables from generated file
    session.create_tables(one_to_one::TABLES);

    // session.drop_database(one_to_one::DATABASE_NAME);

    auto u1 = std::make_shared<one_to_one::User>();
    u1->set_age(24);
    u1->set_degree(4.2);
    u1->set_is_bool(true);
    u1->set_name("stepan");

    auto u2 = std::make_shared<one_to_one::User>();
    u2->set_age(34);
    u2->set_degree(4.7);
    u2->set_is_bool(false);
    u2->set_name("antonuy");

    session.save(u1);
    session.save(u2);


    auto sql = session.select(one_to_one::User::COLUMNS)
        .from(one_to_one::User::TABLE_NAME)
        .where(one_to_one::User::age_in({24, 25, 26}))
        .order_by({{one_to_one::User::AGE, ORDER_DIR::ASC}})
        // .having(one_to_one::User::degree_less_than(5))
        .limit(3)
        .build();

    // std::cout << session.execute(sql)->debug();



    
    // auto sql = session.select(avg(one_to_one::User::AGE).as("avgage"))
    //     .from(one_to_one::User::TABLE_NAME)
    //     // .where(one_to_one::User::age_in({24, 25, 26}))
    //     // .order_by({{one_to_one::User::AGE, ORDER_DIR::ASC}})
    //     // .having(one_to_one::User::degree_less_than(5))
    //     .build();

    auto objects = session.execute(sql)->to_vector_of_maps();

    for(auto obj : objects){
        for(auto [field, value] : obj){
            std::cout << field << ":" << value << std::endl;
        }
        std::cout << "______" << std::endl;
    }
    
    return 0;
}

// between_and



// TODO: CREATE TABLE (create_table/s)
// TODO: INSERT INTO (save, insert_into)
// TODO: SELECT (select, get_by_id, get_all)
// TODO: UPDATE

