find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)

string(CONCAT CLANG_TIDY_CHECKS
    "*,-readability-function-cognitive-complexity,"
    "-altera*,"
    "-cert-dcl03-c,"
    "-misc-static-assert,"
    "-llvm-include-order,"
    "-llvmlibc-*,"
    "-hicpp-*,"
    "-concurrency-mt-unsafe,"
    "-bugprone-easily-swappable-parameters,"
    "-Wdeprecated-declarations,"
    "-cppcoreguidelines-*,"
    "-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling"
)