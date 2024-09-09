function(add_all_tests)
    include(${CMAKE_SOURCE_DIR}/cmake/config.cmake)
    
    if (EXISTS "${CMAKE_SOURCE_DIR}/src/deploy_rc4.c" AND EXISTS "${CMAKE_SOURCE_DIR}/tests/test_rc4.c")
        add_library(rc4_lib SHARED ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c)
        add_executable(test_rc4 ${CMAKE_SOURCE_DIR}/tests/test_rc4.c)
        target_link_libraries(test_rc4 rc4_lib cunit)
        set_target_properties(test_rc4 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
        add_custom_command(TARGET test_rc4 
            POST_BUILD 
            COMMAND strip $<TARGET_FILE:test_rc4>
            WORKING_DIRECTORY ${OUTPUT_DIRECTORY} 
            COMMENT "Striping target") 
    endif()
endfunction()