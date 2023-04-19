#include "allocator.hpp"

int main() {
    SimpleMemoryManager mm;
    mm.create(10);
    void *a4 = mm.get(4);
    void *b1 = mm.get(1);
    void *c4 = mm.get(4);

    void *d8 = mm.get(8);
    void *e2 = mm.get(2);

    void *f4 = mm.get(4);
    void *g4 = mm.get(4);

    void *h4 = mm.get(4);

    mm.destroy(b1);
    mm.destroy(d8);
    mm.destroy(c4);
    mm.destroy(e2);
    mm.destroy(a4);

    mm.destroy(f4);
    mm.destroy(h4);
    mm.destroy(g4);
    mm.clear();
    
//
//    std::map<int, int> a;
//    a.insert({1, 10});
//    a.insert({2, 20});
//    a.insert({3, 30});
//    a.insert({4, 40});
//    a.insert({5, 50});
//
//    std::map<int, int, std::less<>, ReserveAllocator < std::pair<const int, int>, 5>>
//    a2;
//    a2.insert({1, 10});
//    a2.insert({2, 20});
//    a2.insert({3, 30});
//    a2.insert({4, 40});
//    a2.insert({5, 50});
//
//
//    std::for_each(a.cbegin(), a.cend(),
//                  [](const std::pair<int, int> &p) { std::cout << p.first << " " << p.second << std::endl; });
//
//    std::cout << std::endl;
//
//    std::for_each(a2.cbegin(), a2.cend(),
//                  [](const std::pair<int, int> &p) { std::cout << p.first << " " << p.second << std::endl; });

    return 0;
}