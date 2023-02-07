add_executable(test-ip test.cpp)

target_link_libraries(test-ip
    gtest
    gtest_main
)
enable_testing()
add_test(test-ip test-ip)
