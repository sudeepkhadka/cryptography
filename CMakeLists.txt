cmake_minimum_required(VERSION 3.16) 
project(
    deploy_rc4
    LANGUAGES "C"
    DESCRIPTION "Deploy rc4 algorithm"
)

include(cmake/build_system.cmake)

add_all_targets(${CLANG_TIDY_CHECKS})
add_all_tests()