add_executable(test_version test_version.cpp)

if (MSVC)
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_include_directories(test_version PRIVATE "${CMAKE_BINARY_DIR}/helloworld")

target_link_libraries(test_version
    gtest
    gtest_main
)
enable_testing()
add_test(test_version test_version)
