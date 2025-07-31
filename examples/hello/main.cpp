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
    session.create_tables(one_to_one::tables);
    
    //creating objects
    auto John = std::make_shared<one_to_one::User>();
    John->set_name("John");
    auto JohnPass = std::make_shared<one_to_one::Passport>();
    JohnPass->set_num(23);
    John->set_passport(JohnPass);

    auto Mike = std::make_shared<one_to_one::User>();
    Mike->set_name("Mike");
    auto MikePass = std::make_shared<one_to_one::Passport>();
    MikePass->set_num(144);
    John->set_passport(MikePass);

    

    //insert objects into tables 
    session.save<one_to_one::User>(John);
    session.save<one_to_one::User>(Mike);
    

    // auto sql = session.select({}).from(hello::User::TABLE_NAME).build();
    // auto res = session.execute(sql);
    // std::cout << res->debug(hello::User::COLUMN_NAMES);

    // auto users = session.get_all<hello::User>({hello::age_less_or_equal(23)});
    // for(auto user : users){
    //     for(size_t i = 0; i < user->column_names().size(); ++i){
    //         std::cout << user->column_names().at(i) << ":" << user->values().at(i) << std::endl;
    //     }
    //     std::cout << std::endl;
    //     std::cout << std::endl;
    // }

    // auto user = session.get_by_id<hello::User>(4);

    // for(size_t i = 0; i < user->column_names().size(); ++i){
    //     std::cout << user->column_names().at(i) << ":" << user->values().at(i) << std::endl;
    // }
    // std::cout << std::endl;

    // auto select_sql = session.select(hello::User::COLUMN_NAMES).from(hello::User::TABLE_NAME).where(hello::age_between_and(20, 40)).build();

    
    return 0;
}



// TODO: CREATE TABLE (create_table/s)
// TODO: INSERT INTO (save, insert_into)
// TODO: SELECT (select, get_by_id, get_all)
// TODO: UPDATE

