### How to compile and run in linux
`sudo apt-get install clang clang-tidy gcc libssl-dev`
Run `build.sh` 
Output will be inside `bin` directory
run `./bin/deploy_rc4` for running the binary
run `./bin/test_rc4` for testing the binary

For simple rc4 implementation:
run `./bin/simple_rc4` for testing the binary

### How to compile and run in Windows
Uncomment below line from deploy_rc4.c
// #include <Windows.h>
and compile in visual studio
run the output `deploy_rc4.exe` 


#### Files:

**Headers**
header files
**src**
source files
**tests**
test files

CMakeLists.txt [to compile the entire project]
**deprecated**
Older version of Makefile and crypto files from our resource/website


**Issues**
`RC4` is deprecated: Since OpenSSL 3.0. Therefore, Use this to run the binary:
`sudo apt-get install libssl-dev`
`find_package(OpenSSL REQUIRED)`
`target_link_libraries(simple_rc4 OpenSSL::SSL OpenSSL::Crypto)`

added compiler specific directives to remove warnings. 
Do not remove `#pragma` Directives from source file. RC4 is just for testing purpose, it is not safe for use anymore.

Contact @ace aka user@khadsud on discord

**Resource:** 
https://www.oryx-embedded.com/doc/rc4_8c_source.html
