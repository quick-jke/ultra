file(GLOB SCHEMA_SOURCES "src/*.cpp")

add_library(Schema STATIC ${SCHEMA_SOURCES})

target_include_directories(Schema PUBLIC include enum)