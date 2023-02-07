add_executable(test-version test.cpp)

target_include_directories(test-version PRIVATE "${CMAKE_BINARY_DIR}/helloworld")

FetchContent_MakeAvailable(googletest)

target_link_libraries(test-version
    gtest
    gtest_main
)
enable_testing()
add_test(test-version test-version)
