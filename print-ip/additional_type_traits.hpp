#pragma once

#include <type_traits>
#include <string>


template<typename T, typename = void>
struct is_container : std::false_type {
};

template<>
struct is_container<std::basic_string<char>> : std::false_type {
};

template<typename T>
struct is_container<T,
        std::void_t<decltype(std::declval<T &>().begin()),
                decltype(std::declval<T &>().end()),
                typename T::value_type >> : std::true_type {
};


template<typename T, typename ... Args>
struct is_one_type : std::true_type {
};

template<typename T>
struct is_one_type<T> : std::true_type {
};

template<typename T, typename U, typename ...Args>
struct is_one_type<T, U, Args...> {
    static constexpr auto value = std::is_same_v<T, U> && is_one_type<U, Args...>::value;
};