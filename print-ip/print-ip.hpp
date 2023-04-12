#pragma once

#include <iostream>
#include "additional_type_traits.hpp"

/// \mainpage   Print an IP-address for C++
///
/// \brief      Print an IP-address from various data.
/// \author     Nameless
/// \details
/// This function prints an IP address of various data types to the standard input output stream.\n
/// \n
/// Exsample: \n
/// \n
/// print_ip( int8_t{-1} ); // 255 \n
/// print_ip( int16_t{0} ); // 0.0 \n
/// print_ip( int32_t{2130706433} ); // 127.0.0.1 \n
/// print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41 \n
/// print_ip( std::string{“Hello, World!”} ); // Hello, World! \n
/// print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400 \n
/// print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100 \n
/// print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0 \n
///


/// \brief Print an IP-address for integer type
/// \tparam Integer integer type
/// \param ip The integer type reference
template<typename Integer, std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
void print_ip(const Integer &ip) {
    auto *start = reinterpret_cast<const unsigned char *> (&ip);
    size_t size = sizeof(Integer);
    start += size - 1;
    for (const unsigned char *it = start; size > 0; --it, --size) {
        if (it != start)
            std::cout << ".";
        std::cout << static_cast<int>(*it);
    }
    std::cout << std::endl;
}

/// \brief Print an IP-address for container
/// \tparam Container container type
/// \param ip The container type reference
template<typename Container, std::enable_if_t<is_container<Container>::value, bool> = true>
void print_ip(const Container &ip) {
    for (auto it = ip.cbegin(); it != ip.cend(); ++it) {
        if (it != ip.cbegin())
            std::cout << ".";
        std::cout << *it;
    }
    std::cout << std::endl;
}

/// \brief Print a raw std string
/// \tparam String std string
/// \param ip The string type reference
template<typename String, std::enable_if_t<std::is_same_v<String, std::basic_string<char>>, bool> = true>
void print_ip(const String &ip) {
    std::cout << ip << std::endl;
}

/// \brief This is an internal function for: void print_ip(const std::tuple<Args...> ip)
template<typename TupleT, std::size_t... Is>
void print_elements(const TupleT &tp, const std::index_sequence<Is...>) {
    size_t index = 0;
    auto print_element = [&index](const auto &x) {
        if (index != 0) {
            std::cout << ".";
        }
        std::cout << x;
        ++index;
    };
    (print_element(std::get<Is>(tp)), ...);
}

/// \brief Print an IP-address for std::typle. \n std::typle types must be the same.
/// \tparam Args args of the same type
/// \param ip The std::typle
template<typename ... Args, std::enable_if_t<is_one_type<Args...>::value, bool> = true>
void print_ip(const std::tuple<Args...> ip) {
    print_elements(ip, std::make_index_sequence<std::tuple_size<decltype(ip)>::value>{});
}
