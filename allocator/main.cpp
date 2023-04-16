#include "allocator.hpp"
#include <map>
#include <vector>

int main() {

    std::map<int, int> a;
    a.insert({1, 10});
    a.insert({2, 20});
    a.insert({3, 30});
    a.insert({4, 40});
    a.insert({5, 50});

    std::map<int, int, std::less<>, MyAllocator < std::pair<const int, int>, 5>>
    a2;
    a2.insert({1, 10});
    a2.insert({2, 20});
    a2.insert({3, 30});
    a2.insert({4, 40});
    a2.insert({5, 50});


    std::for_each(a.cbegin(), a.cend(),
                  [](const std::pair<int, int> &p) { std::cout << p.first << " " << p.second << std::endl; });

    std::cout << std::endl;

    std::for_each(a2.cbegin(), a2.cend(),
                  [](const std::pair<int, int> &p) { std::cout << p.first << " " << p.second << std::endl; });

    return 0;
}