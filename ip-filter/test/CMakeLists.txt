set(TARGET_NAME test-ip-convert)
add_executable(${TARGET_NAME} test.cpp)

FetchContent_MakeAvailable(googletest)

target_link_libraries(${TARGET_NAME}
    gtest
    gtest_main
)
enable_testing()
add_test(${TARGET_NAME} ${TARGET_NAME})
