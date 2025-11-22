file(GLOB SQL_SOURCES "src/*.cpp")

add_library(Sql STATIC ${SQL_SOURCES})

target_include_directories(Sql PUBLIC include enum interfaces)
