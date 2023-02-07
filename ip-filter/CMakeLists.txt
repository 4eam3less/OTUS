set(PACKAGE_NAME "ip-filter")

project(ip-filter)
add_subdirectory(test)

add_executable(ip-filter ip.hpp ip_filter.cpp)

