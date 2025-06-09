#include "driver_factory.hpp"
#include "mysql_driver.hpp"
#define HAVE_MYSQL
#ifdef HAVE_MYSQL
    #include "mysql_driver.hpp"
#endif

#ifdef HAVE_POSTGRESQL
    #include "postgres_driver.hpp"
#endif
namespace quick {
namespace ultra {
std::shared_ptr<IDriver> DriverFactory::create(const std::string& driver_type) {
    if (driver_type == "mysql") {
        #ifdef HAVE_MYSQL
            return std::make_shared<MySQLDriver>();
        #else
            throw std::runtime_error("MySQL driver not available (not compiled in)");
        #endif
    }
    else if (driver_type == "postgres" || driver_type == "postgresql") {
        #ifdef HAVE_POSTGRESQL
            return std::make_shared<PostgreSQLDriver>();
        #else
            throw std::runtime_error("PostgreSQL driver not available (not compiled in)");
        #endif
    }
    else {
        throw std::runtime_error("Unknown driver type: " + driver_type);
    }
}
}}// namespace quick::ultra
