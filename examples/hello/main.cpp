#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models.hpp"


int main() {
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect("host=localhost;user=root;password=RootPass123!;database=" + hello::DATABASE_NAME);
    quick::ultra::Session session(driver);
    // session.drop_database(hello::DATABASE_NAME);
    session.create_tables(hello::tables);
    // session.execute("use " + hello::DATABASE_NAME);
    

    auto user1 = std::make_shared<hello::User>();
    user1->set_name("John");
    user1->set_age(23);
    user1->set_email("John@icloud.com");
    user1->set_password("qweqweqwe");

    // auto user2 = std::make_shared<hello::User>();
    // user2->set_name("Maty");
    // user2->set_age(43);
    // user2->set_email("Maty@icloud.com");
    // user2->set_password("zxczxczxc");

    // auto user3 = std::make_shared<hello::User>();
    // user3->set_name("Adam");
    // user3->set_age(34);
    // user3->set_email("Adam@icloud.com");
    // user3->set_password("asdasdasd");

    session.save(user1);

    // auto sql = session.select({}).from(hello::User::TABLE_NAME).build();
    // auto res = session.execute(sql);
    // std::cout << res->debug(hello::User::COLUMN_NAMES);

    auto user = session.get<hello::User>(1);
    std::cout << user->age() << std::endl;

    // auto select_sql = session.select(hello::User::COLUMN_NAMES).from(hello::User::TABLE_NAME).where(user1->age_between_and(20, 40)).build();


    //User user1 = session.load<User>()
    

    // Загрузка объекта из БД по ID
    // User loaded_user = session.load<User>(1); // SELECT * FROM users WHERE id=1
    // std::cout << loaded_user.name << std::endl;

    // Выборка по условию
    // auto users = session.query<User>()
    //              .where("email LIKE '%example.com'")
    //              .limit(10)
    //              .execute();

    
    return 0;
}
