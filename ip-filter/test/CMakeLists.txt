add_executable(test-ip test.cpp)

FetchContent_MakeAvailable(googletest)

target_link_libraries(test-ip
    gtest
    gtest_main
)
enable_testing()
add_test(test-ip test-ip)
