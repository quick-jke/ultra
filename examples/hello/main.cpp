#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models.hpp"


int main() {
    //init driver
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect("host=localhost;user=root;password=RootPass123!;database=" + hello::DATABASE_NAME);
    //init session
    quick::ultra::Session session(driver);

    //creating tables from generated file
    session.create_tables(hello::tables);
    
    //creating objects
    auto user1 = std::make_shared<hello::User>();
    user1->set_name("John");
    user1->set_age(23);
    user1->set_email("John@icloud.com");
    user1->set_password("qweqweqwe");

    auto user2 = std::make_shared<hello::User>();
    user2->set_name("Maty");
    user2->set_age(43);
    user2->set_email("Maty@icloud.com");
    user2->set_password("zxczxczxc");

    auto user3 = std::make_shared<hello::User>();
    user3->set_name("Adam");
    user3->set_age(34);
    user3->set_email("Adam@icloud.com");
    user3->set_password("asdasdasd");


    auto user4 = std::make_shared<hello::User>();
    user4->set_name("Rachel");
    user4->set_age(18);
    user4->set_email("Rachel@icloud.com");
    user4->set_password("][p][p][p]");

    auto user5 = std::make_shared<hello::User>();
    user5->set_name("Tony");
    user5->set_age(13);
    user5->set_email("Tony@icloud.com");
    user5->set_password("bnmbnmbnm");

    //insert objects into tables 
    session.save<hello::User>(user1);
    session.save<hello::User>(user2);
    session.save<hello::User>(user3);
    session.save<hello::User>(user4);
    session.save<hello::User>(user5);

    // auto sql = session.select({}).from(hello::User::TABLE_NAME).build();
    // auto res = session.execute(sql);
    // std::cout << res->debug(hello::User::COLUMN_NAMES);

    auto users = session.get_all<hello::User>({hello::age_less_or_equal(23)});
    for(auto user : users){
        for(size_t i = 0; i < user->column_names().size(); ++i){
            std::cout << user->column_names().at(i) << ":" << user->values().at(i) << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    auto user = session.get_by_id<hello::User>(4);

    for(size_t i = 0; i < user->column_names().size(); ++i){
        std::cout << user->column_names().at(i) << ":" << user->values().at(i) << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    auto select_sql = session.select(hello::User::COLUMN_NAMES).from(hello::User::TABLE_NAME).where(hello::age_between_and(20, 40)).build();

    
    return 0;
}



// TODO: CREATE TABLE (create_table/s)
// TODO: INSERT INTO (save, insert_into)
// TODO: SELECT (select, get_by_id, get_all)
// TODO: UPDATE

