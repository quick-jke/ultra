
find_package(Python REQUIRED COMPONENTS Interpreter)

set(GENERATE_SCRIPT ${PROJECT_SOURCE_DIR}/ultra/scripts/generate_helper.py)
set(GENERATED_DIR ${PROJECT_BINARY_DIR}/generated)

file(MAKE_DIRECTORY ${GENERATED_DIR})
include_directories(${GENERATED_DIR})

add_custom_target(
    generate_output_file
    COMMAND ${Python_EXECUTABLE} ${GENERATE_SCRIPT}
    ARGS --output=${GENERATED_DIR}/session_helper.hpp
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating session_helper.hpp"
)



file(GLOB CORE_SOURCES "src/*.cpp")
add_library(Core STATIC ${CORE_SOURCES})
target_include_directories(Core PUBLIC include ${PROJECT_BINARY_DIR}/generated)
target_link_libraries(Core PUBLIC Driver Sql)

add_dependencies(Core generate_output_file)


