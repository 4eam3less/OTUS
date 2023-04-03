#pragma once

#include <iostream>
#include "additional_type_traits.hpp"

/// test func
/// \tparam Integer
/// \param ip
template<typename Integer,  std::enable_if_t<std::is_integral<Integer>::value, bool > = true >
void print_ip(const Integer &ip){
    auto *start = reinterpret_cast<const unsigned char*> (&ip);
    size_t size = sizeof(Integer);
    start += size - 1;
    for(const unsigned char *it = start; size > 0; --it, --size){
        if (it != start)
            std::cout << ".";
        std::cout << static_cast<int>(*it);
    }
    std::cout << std::endl;
}

template<typename T, std::enable_if_t<is_container<T>::value, bool> = true >
void print_ip(const T &ip){
    for(auto it = ip.cbegin(); it != ip.cend(); ++it) {
        if (it != ip.cbegin())
            std::cout << ".";
        std::cout << *it;
    }
    std:: cout << std::endl;
}

template<typename String, std::enable_if_t<std::is_same_v<String, std::basic_string<char>>, bool> = true>
void print_ip(const String &ip){
    std::cout << ip << std::endl;
}

template <typename TupleT, std::size_t... Is>
void print_elements(const TupleT& tp, const std::index_sequence<Is...>) {
    size_t index = 0;
    auto print_element = [&index](const auto& x) {
        if(index != 0){
            std::cout << ".";
        }
        std::cout << x;
        ++index;
    };
    (print_element(std::get<Is>(tp)), ...);
}

template<typename ... Args, std::enable_if_t<is_one_type<Args...>::value, bool> = true >
void print_ip(const std::tuple<Args...> ip) {
    print_elements(ip, std::make_index_sequence<std::tuple_size<decltype(ip)>::value>{});
}
