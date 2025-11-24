#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models/one_to_one.hpp"


using namespace quick::ultra::sqljke;
int main() {
    //init driver
    auto driver = quick::ultra::DriverFactory::create(quick::ultra::DRIVER_TYPE::MS_SQL);
    driver->connect(quick::ultra::to_connection_string("localhost", "root", "root7423", one_to_one::DATABASE_NAME));
    //init session
    quick::ultra::Session session(driver);

    //creating tables from generated file
    session.create_tables(one_to_one::TABLES);

    // session.drop_database(one_to_one::DATABASE_NAME);

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


    // auto sql = session.select(one_to_one::User::COLUMNS)
    //     .from(one_to_one::User::TABLE_NAME)
    //     // .where(one_to_one::User::age_in({24, 25, 26}))
    //     .where(Expression(one_to_one::User::AGE).more_than(25))
    //     .order_by({{one_to_one::User::AGE, ORDER_DIR::ASC}})
    //     // .having(one_to_one::User::degree_less_than(5))
    //     .limit(3)
    //     .build();

    // std::cout << session.execute(sql)->debug();



    
    auto sql = session.select({
        one_to_one::User::AGE,
        count().as("user_count"),
        avg(one_to_one::User::DEGREE).as("avg_degree"),
        min(one_to_one::User::DEGREE).as("min_degree"),
        max(one_to_one::User::DEGREE).as("max_degree"),
        sum(one_to_one::User::IS_BOOL).as("active_count")
    })
        .from(one_to_one::User::TABLE_NAME)
        .group_by({one_to_one::User::AGE})
        .order_by({{one_to_one::User::AGE, ORDER_DIR::ASC}})
        // .where(Expression(one_to_one::User::AGE).in(std::vector<int>{24, 25, 26}))
        // .order_by({{one_to_one::User::AGE, ORDER_DIR::ASC}})
        // .having(one_to_one::User::degree_less_than(5))
        .build();

    std::cout << session.execute(sql)->debug();


    
    return 0;
}

// between_and



// TODO: CREATE TABLE (create_table/s)
// TODO: INSERT INTO (save, insert_into)
// TODO: SELECT (select, get_by_id, get_all)
// TODO: UPDATE

