#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models/one_to_one.hpp"

using namespace quick::ultra::sqljke;

int main() {
    auto driver = quick::ultra::DriverFactory::create(quick::ultra::DRIVER_TYPE::MS_SQL);
    driver->connect(quick::ultra::to_connection_string("localhost", "root", /*"rootjke7423"*/ "dev_password", one_to_one::DATABASE_NAME, 3306));
    quick::ultra::Session session(driver);

    session.create_tables(one_to_one::TABLES);

    auto p = std::make_shared<one_to_one::Passport>();
    p->set_num(23);

    auto users = std::vector<std::shared_ptr<one_to_one::User>>{
        // 1
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("antony"); u->set_age(34); u->set_degree(4.7); u->set_is_bool(false);
            u->set_passport(p);
            return u;
        }(),
        // 2
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("maria"); u->set_age(22); u->set_degree(4.2); u->set_is_bool(true);
            u->set_passport(p);
            return u;
        }(),
        // 3
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("ivan"); u->set_age(34); u->set_degree(3.8); u->set_is_bool(false);
            u->set_passport(p);
            return u;
        }(),
        // 4
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("olga"); u->set_age(22); u->set_degree(4.9); u->set_is_bool(true);
            u->set_passport(p);
            return u;
        }(),
        // 5
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("petr"); u->set_age(34); u->set_degree(4.7); u->set_is_bool(true);
            u->set_passport(p);
            return u;
        }(),
        // 6
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("anna"); u->set_age(28); u->set_degree(3.5); u->set_is_bool(false);
            u->set_passport(p);
            return u;
        }(),
        // 7
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("dmitry"); u->set_age(28); u->set_degree(4.0); u->set_is_bool(false);
            u->set_passport(p);
            return u;
        }(),
        // 8
        [p]{
            auto u = std::make_shared<one_to_one::User>();
            u->set_name("elena"); u->set_age(22); u->set_degree(4.2); u->set_is_bool(false);
            u->set_passport(p);
            return u;
        }()
    };

    for(const auto& user : users){
        session.save(user);
    }

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

    std::cout << session.execute(sql)->debug() << std::endl;


    // auto update_sql = session.update(one_to_one::User::TABLE_NAME).set(one_to_one::User::IS_BOOL, 1).where(Expression(one_to_one::User::IS_BOOL).equal(0)).build();
    // session.execute(update_sql);

    // auto select_sql = session.select({}).from(one_to_one::User::TABLE_NAME).build();
    // std::cout << session.execute(select_sql)->debug() << std::endl;



    return 0;

}



