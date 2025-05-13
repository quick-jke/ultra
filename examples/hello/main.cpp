#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <iostream>

int main() {
    try {
        // Подключение к базе данных
        // auto driver = quick::ultra::DriverFactory::create("mysql");
        // driver->connect("host=localhost;user=root;password=secret;database=testdb");

        // Создание таблицы на основе класса
        // orm::Session session(driver);
        // session.create_table<User>();

        // Сохранение объекта в БД
        // User user;
        // user.name = "Alice";
        // user.email = "alice@example.com";
        // session.save(user);

        // Загрузка объекта из БД по ID
        // User loaded_user = session.load<User>(1); // SELECT * FROM users WHERE id=1
        // std::cout << loaded_user.name << std::endl;

        // Выборка по условию
        // auto users = session.query<User>()
        //              .where("email LIKE '%example.com'")
        //              .limit(10)
        //              .execute();

        sql::mysql::MySQL_Driver *driver;
        
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "RootPass123!");

        sql::Statement *stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS test_database");

        con->setSchema("test_database");

        

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

    return 0;
}