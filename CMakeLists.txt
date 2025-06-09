cmake_minimum_required(VERSION 3.14)
project(qultra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ultra)


add_executable(${PROJECT_NAME} examples/hello/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ultra
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_BINARY_DIR}/build
)
