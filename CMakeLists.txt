cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(global CXX)

if(MSVC)
    add_compile_options(/W4
    )
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror
    )
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.0
)

if(DEFINED SOLUTION)
    if(SOLUTION STREQUAL "homework1")
        add_subdirectory(helloworld)
    elseif(SOLUTION STREQUAL "homework2")
        add_subdirectory(ip-filter)
    endif()
endif()
