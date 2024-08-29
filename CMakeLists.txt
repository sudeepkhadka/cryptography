cmake_minimum_required(VERSION 3.16) 
project(
    deploy_rc4
    LANGUAGES "C"
    DESCRIPTION "Deploy rc4 algorithm"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_compile_options(-Wall -O3 -Wextra -pedantic --std=c17)
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/deploy_rc4.c)


if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/deploy_rc4.c)
    add_library(rc4_lib SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/deploy_rc4.c)
    add_executable(test_rc4 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rc4.c)
    target_link_libraries(test_rc4 rc4_lib cunit)
endif()
