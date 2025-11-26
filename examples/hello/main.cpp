#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models/one_to_one.hpp"

using namespace quick::ultra::sqljke;

int main() {
    auto driver = quick::ultra::DriverFactory::create(quick::ultra::DRIVER_TYPE::MS_SQL);
    driver->connect(quick::ultra::to_connection_string("localhost", "root", "root7423", one_to_one::DATABASE_NAME));
    quick::ultra::Session session(driver);

    session.create_tables(one_to_one::TABLES);


    auto users = std::vector<std::shared_ptr<one_to_one::User>>{
        // 1
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("antonuy"); u->set_age(34); u->set_degree(4.7); u->set_is_bool(false);
            return u;
        }(),
        // 2
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("maria"); u->set_age(22); u->set_degree(4.2); u->set_is_bool(true);
            return u;
        }(),
        // 3
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("ivan"); u->set_age(34); u->set_degree(3.8); u->set_is_bool(false);
            return u;
        }(),
        // 4
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("olga"); u->set_age(22); u->set_degree(4.9); u->set_is_bool(true);
            return u;
        }(),
        // 5
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("petr"); u->set_age(34); u->set_degree(4.7); u->set_is_bool(true);
            return u;
        }(),
        // 6
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("anna"); u->set_age(28); u->set_degree(3.5); u->set_is_bool(false);
            return u;
        }(),
        // 7
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("dmitry"); u->set_age(28); u->set_degree(4.0); u->set_is_bool(false);
            return u;
        }(),
        // 8
        []{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("elena"); u->set_age(22); u->set_degree(4.2); u->set_is_bool(false);
            return u;
        }()
    };

    for(const auto& user : users){
        session.save(user);
    }


    auto pass = std::make_shared<one_to_one::Passport>();

    // users.at(0)->set_passport(pass);
    
    auto sql = session.select({
        Column(one_to_one::User::AGE).as("age_group"),
        count().as("user_count"),
        round(avg(one_to_one::User::DEGREE), 2).as("avg_degree"),
        min(one_to_one::User::DEGREE).as("min_degree"),
        max(one_to_one::User::DEGREE).as("max_degree"),
        sum(one_to_one::User::IS_BOOL).as("active_count")
    })
        .from(one_to_one::User::TABLE_NAME)
        .group_by({one_to_one::User::AGE})
        .order_by({{one_to_one::User::AGE, ORDER_DIR::ASC}})
        .build();

    auto objects = session.execute(sql)->to_vector_of_maps();

    for(auto obj : objects){
        for(auto [field, value] : obj){
            std::cout << field << ":" << value << std::endl;
        }
        std::cout << "=================" << std::endl;
    }

    std::cout << objects.at(1)["min_degree"] << std::endl;


    
    return 0;
}


