#include <iostream>

#include "driver_factory.hpp"
#include "session.hpp"
#include "build/models.hpp"


int main() {
    // Подключение к базе данных
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect("host=localhost;user=root;password=RootPass123!;database=hello");

    //Создание таблиц на основе entity из models
    quick::ultra::Session session(driver);
    session.create_tables(hello::pure_tables);
    // session.select();
    // session.insert_into();

    // // Сохранение объекта в БД
    // User user;
    // user.name = "Rachel";
    // user.email = "Rachel@example.com";
    // user.products = {new Product(), new Product()};
    // session.save(user);
    

    // Загрузка объекта из БД по ID
    // User loaded_user = session.load<User>(1); // SELECT * FROM users WHERE id=1
    // std::cout << loaded_user.name << std::endl;

    // Выборка по условию
    // auto users = session.query<User>()
    //              .where("email LIKE '%example.com'")
    //              .limit(10)
    //              .execute();


//old
/*
    stmt->execute(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "name VARCHAR(100)"
        ")"
    );

    sql::ResultSet *res = stmt->executeQuery("SELECT COUNT(*) FROM users");
    res->next();
    int count = res->getInt(1);
    delete res;

    if (count == 0) {
        stmt->execute("INSERT INTO users (name) VALUES ('Alice'), ('Bob'), ('Charlie')");
        std::cout << "Тестовые данные добавлены" << std::endl;
    }

    res = stmt->executeQuery("SELECT id, name FROM users");

    while (res->next()) {
        int id = res->getInt("id");
        std::string name = res->getString("name");
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }

    delete res;
    delete stmt;
    delete con;

    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        std::cerr << "Error Code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQL State: " << e.getSQLState() << std::endl;
    }
*/
    return 0;
}



/*
std::cout << "ID\tName\tAge\n";
    
while (result->next()) {
    int id = result->get_int("id");
    std::string name = result->get_string("name");
    int age = result->get_int("age");

    std::cout << id << "\t" << name << "\t" << age << "\n";
}
*/
