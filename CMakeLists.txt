cmake_minimum_required(VERSION 3.14)
project(qultra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ultra/drivers)

add_executable(${PROJECT_NAME} examples/hello/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Driver
        mysqlcppconn
)