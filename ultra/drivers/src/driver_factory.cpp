#include "driver_factory.hpp"
#include "mysql_driver.hpp"
#define HAVE_MYSQL
#ifdef HAVE_MYSQL
    #include "mysql_driver.hpp"
#endif

#ifdef HAVE_POSTGRESQL
    #include "postgres_driver.hpp"
#endif
namespace quick::ultra {

std::shared_ptr<IDriver> DriverFactory::create(const DRIVER_TYPE& driver_type) {
    switch (driver_type)
    {
        case DRIVER_TYPE::MS_SQL: {
            #ifdef HAVE_MYSQL
                return std::make_shared<MySQLDriver>();
            #else
                throw std::runtime_error("MySQL driver not available (not compiled in)");
            #endif
        }
        
        case DRIVER_TYPE::POSTGRE_SQL: {
            #ifdef HAVE_POSTGRESQL
                return std::make_shared<PostgreSQLDriver>();
            #else
                throw std::runtime_error("PostgreSQL driver not available (not compiled in)");
            #endif
        }
        default: {
            throw std::runtime_error("Unknown driver type");
        }
    }
}
}// namespace quick::ultra
