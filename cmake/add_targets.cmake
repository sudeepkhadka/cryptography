function(add_all_targets CMAKE_CHECKS)
    include(${CMAKE_SOURCE_DIR}/cmake/config.cmake)
    set(COMPILE_OPT -Wall -O3 -Wextra -pedantic --std=c17)
    
    add_executable(keylogger ${CMAKE_SOURCE_DIR}/src/keylogger.c)

    if (EXISTS ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c)
        add_executable(deploy_rc4 ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c)
        set_target_properties(${target} PROPERTIES COMPILE_OPTIONS ${COMPILE_OPT})
    endif()
    
    if (EXISTS ${CMAKE_SOURCE_DIR}/src/simple_rc4.c)
        find_package(OpenSSL REQUIRED)
        add_executable(simple_rc4 ${CMAKE_SOURCE_DIR}/src/simple_rc4.c)
        target_link_libraries(simple_rc4 OpenSSL::SSL OpenSSL::Crypto)
        add_compile_options(-g3 -O3)
    endif()

    set(TARGETS_LIST deploy_rc4 simple_rc4)

    # Strip all the release executable to reduce its size
    foreach(target ${TARGETS_LIST})
        add_custom_command(TARGET ${target}
            POST_BUILD # run command after target has built
            COMMAND strip $<TARGET_FILE:${target}> #strip the output binary
            WORKING_DIRECTORY ${OUTPUT_DIRECTORY}
            COMMENT "Stripping ${target} executable"
        )
        set_target_properties(${target} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
    endforeach()
    

    # set the compile options and definitions for both build types
    set(CMAKE_C_CLANG_TIDY "clang-tidy" "-checks=${CMAKE_CHECKS}" "-warnings-as-errors=*")

endfunction()