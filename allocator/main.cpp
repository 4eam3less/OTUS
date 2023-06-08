#include "reserve-allocator.hpp"
#include <map>
#include <iostream>
#include <algorithm>
#include "list.hpp"

size_t factorial(unsigned int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main() {

    std::map<int, int> a;
    std::map<int, int, std::less<>, ReserveAllocator<std::pair<const int, int>, 10>> b;
    List<int, std::allocator<Node<int>>> standard_list;
    List<int, ReserveAllocator<Node<int>, 10>> reserve_list;

    for (size_t i = 0; i < 10; ++i) {
        a.insert({i, factorial(i)});
        b.insert({i, factorial(i)});
        standard_list.push_back(i);
        reserve_list.push_back(i);
    }

    auto print_map = [](auto &it) {
        std::cout << it.first << " " << it.second << std::endl;
    };
    std::for_each(a.cbegin(), a.cend(), print_map);
    std::for_each(b.cbegin(), b.cend(), print_map);

    auto print_list = [](const Node<int> &it) {
        std::cout << it.data << " ";
    };
    std::for_each(standard_list.cbegin(), standard_list.cend(), print_list);
    std::cout << std::endl;
    std::for_each(reserve_list.cbegin(), reserve_list.cend(), print_list);
    std::cout << std::endl;

    auto copy_list = standard_list;
    standard_list.clear();
    std::for_each(copy_list.cbegin(), copy_list.cend(), print_list);

    return 0;
}
