file(GLOB SCANNER_SOURCES "src/*.cpp")

add_library(Scanner STATIC ${SCANNER_SOURCES})

target_include_directories(Scanner PUBLIC include)

target_link_libraries(Scanner PUBLIC Utils)