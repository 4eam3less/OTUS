#include "reserve-allocator.hpp"
#include <map>
#include <iostream>

size_t factorial(unsigned int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main() {

    std::map<int, int> a;
    std::map<int, int, std::less<>, ReserveAllocator<std::pair<const int, int>, 10>> b;

    for (size_t i = 0; i < 10; ++i) {
        a.insert({i, factorial(i)});
        b.insert({i, factorial(i)});
    }

    auto print = [](auto it) {
        std::cout << it.first << " " << it.second << std::endl;
    };

    std::for_each(a.cbegin(), a.cend(), print);
    std::for_each(b.cbegin(), b.cend(), print);

    return 0;
}
