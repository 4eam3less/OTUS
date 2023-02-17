set(TARGET_NAME ip-filter)

add_subdirectory(test)

add_executable(${TARGET_NAME} ip-convert.hpp ip-filter.cpp)

