#sources.cmake -- to add all the sources and add to executable in 
# build system/CMakelists.txt

set (SOURCES 
   ${CMAKE_SOURCE_DIR}/src/deploy_rc4.c
   ${CMAKE_SOURCE_DIR}/src/simple_rc4.c
)

set (TESTS
   ${CMAKE_SOURCE_DIR}/tests/test_rc4.c
)