cmake_minimum_required(VERSION 3.14)
project(qultra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_BINARY_DIR}/models)
add_subdirectory(ultra)
add_custom_target(copy_models ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples/models ${CMAKE_BINARY_DIR}/models
    COMMENT "Copying models folder to build directory"
)

add_executable(${PROJECT_NAME} examples/hello/main.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ultra
)