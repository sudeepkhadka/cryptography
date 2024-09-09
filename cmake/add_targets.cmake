function(add_all_targets CMAKE_CHECKS)
    set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(COMPILE_OPT -Wall -O3 -Wextra -pedantic --std=c17)
    
    if (EXISTS ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c)
        add_executable(deploy_rc4 ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c)
    endif()
    
    if (EXISTS ${CMAKE_SOURCE_DIR}/src/simple_rc4.c)
        add_executable(simple_rc4 ${CMAKE_SOURCE_DIR}/src/simple_rc4.c)
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
        set_target_properties(${target} PROPERTIES COMPILE_OPTIONS ${COMPILE_OPT})
    endforeach()

    # set the compile options and definitions for both build types
    set(CMAKE_C_CLANG_TIDY "clang-tidy" "-checks=${CMAKE_CHECKS}" "-warnings-as-errors=*")

endfunction()