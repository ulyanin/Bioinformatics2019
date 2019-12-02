#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>

template <class C>
std::ostream& PrintContainer(C c, std::string_view splitter = " ", std::ostream& os = std::cout) {
    for (auto it = c.begin(); it != c.end(); ++it) {
        if (it != c.begin()) {
            os << splitter;
        }
        os << (*it);
    }
    return os;
}

std::ostream& PrintPermutation(const std::vector<int>& p, std::ostream& os = std::cout) {
    os << std::showpos << "(";
    PrintContainer(p, " ", os) << ")" << std::endl;
    return os;
}

std::vector<int> ReadPermutation() {
    char tmp;
    std::cin >> tmp;
    std::vector<int> p;
    for (int k; std::cin >> k; ) {
        p.push_back(k);
    }
    return p;
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::vector<int> p = ReadPermutation();
    PrintPermutation(p);
    p.push_back(p.size() + 1);
    size_t ans = 0;
    ans += p[0] != 1;
    for (size_t i = 1; i < p.size(); ++i) {
        if (p[i] - p[i - 1] != 1) {
            ++ans;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}