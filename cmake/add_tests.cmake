function(add_all_tests)
    set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    
    if (EXISTS "${CMAKE_SOURCE_DIR}/src/deploy_rc4.c" AND EXISTS "${CMAKE_SOURCE_DIR}/tests/test_rc4.c")
        add_library(rc4_lib SHARED ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c)
        add_executable(test_rc4 ${CMAKE_SOURCE_DIR}/tests/test_rc4.c)
        target_link_libraries(test_rc4 rc4_lib cunit)
    endif()
endfunction()