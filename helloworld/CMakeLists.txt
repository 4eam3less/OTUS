set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(PACKAGE_NAME "helloworld")

project(helloworld VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

add_executable(helloworld main.cpp)

target_include_directories(helloworld PRIVATE "${CMAKE_BINARY_DIR}/helloworld")

add_subdirectory(test EXCLUDE_FROM_ALL)

install(TARGETS helloworld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_NAME ${PACKAGE_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT 4eam3less@gmail.com)

include(CPack)
