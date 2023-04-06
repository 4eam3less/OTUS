set(TARGET_NAME print-ip)


set(HEADERS print-ip.hpp additional_type_traits)
set(SOURCES print-ip.cpp)

add_executable(${TARGET_NAME} ${HEADERS} ${SOURCES})
