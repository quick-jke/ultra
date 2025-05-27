add_library(ultra INTERFACE)

add_subdirectory(core)
add_subdirectory(drivers)
add_subdirectory(scanner)
add_subdirectory(schema)
add_subdirectory(sql)

target_link_libraries(ultra
    INTERFACE
        Core
        Driver
        Scanner
        Schema
        Sql
        mysqlcppconn
)


target_include_directories(ultra
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)