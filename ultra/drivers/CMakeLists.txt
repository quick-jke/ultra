
file(GLOB DRIVER_SOURCES "src/*.cpp")

add_library(Driver STATIC ${DRIVER_SOURCES})

target_include_directories(Driver 
    PUBLIC 
        /usr/include/mysql-cppconn8
        include
        mysqlcppconn
        mysqlclient
        
)
target_link_libraries(Driver PUBLIC Sql)



