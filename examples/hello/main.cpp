#include <iostream>

#include "driver_factory.hpp"

int main() {
    // Подключение к базе данных
    auto driver = quick::ultra::DriverFactory::create("mysql");
    driver->connect("host=localhost;user=root;password=root;database=testdb");

    
//new
/*
    Создание таблицы на основе класса
    quick::ultra::Session session(driver);
    session.create_table<User>();

    Сохранение объекта в БД
    User user;
    user.name = "Alice";
    user.email = "alice@example.com";
    session.save(user);

    Загрузка объекта из БД по ID
    User loaded_user = session.load<User>(1); // SELECT * FROM users WHERE id=1
    std::cout << loaded_user.name << std::endl;

    Выборка по условию
    auto users = session.query<User>()
                 .where("email LIKE '%example.com'")
                 .limit(10)
                 .execute();
*/

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