file(GLOB CORE_SOURCES "src/*.cpp")
add_library(Core STATIC ${CORE_SOURCES})
target_include_directories(Core PUBLIC include enum)
target_link_libraries(Core PUBLIC Driver Sql)



