#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

inline std::vector<uint8_t> convert_ip_to_vector(const std::string &str){

    std::regex ipv4("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    if(!std::regex_match(str, ipv4)){
       throw std::runtime_error ("Incorrect ip structure");
    }

    std::vector<uint8_t> result;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of('.');
    constexpr int max_value_ip = 256;

    while(stop != std::string::npos){
        if(int value = stoi((str.substr(start, stop - start))); value < max_value_ip && value >= 0) [[likely]]
            result.push_back(value);
        else [[unlikely]]
            throw std::runtime_error ("Incorrect ip range");

        start = stop + 1;
        stop = str.find_first_of('.', start);
    }
    result.push_back(stoi(str.substr(start)));
    return result;
}

inline void  print_ip(const std::vector<uint8_t> &ip){
    for(auto it = ip.cbegin(); it != ip.cend(); ++it){
        if (it != ip.cbegin())
            std::cout << ".";
        std::cout << static_cast<int>(*it);
    }
    std::cout << std::endl;
}

template <class Filter, class Handler>
inline void ip_filter(const std::vector<std::vector<uint8_t>> & ip_pool, Filter &&filter, Handler &&handler){
    for(auto &it : ip_pool)
        if(filter(it))
            handler(it);
}
