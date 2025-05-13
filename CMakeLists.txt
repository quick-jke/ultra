cmake_minimum_required(VERSION 3.14)
project(ultra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/usr/include/mysql-cppconn8)

add_executable(${PROJECT_NAME} examples/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        mysqlcppconn
        mysqlclient
)