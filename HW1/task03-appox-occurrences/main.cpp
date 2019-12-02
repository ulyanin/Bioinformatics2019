#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_set>

template <class C>
void PrintCollection(const C& collection, std::ostream& os = std::cout) {
    for (const auto& elem : collection) {
        os << elem << " ";
    }
    os << std::endl;
}

size_t HammingDistance(std::string_view a, std::string_view b) {
    assert(a.length() == b.length());
    size_t dist = 0;
    for (size_t i = 0; i < a.length(); ++i) {
        dist += (a[i] != b[i]);
    }
    return dist;
}


int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    std::string t;
    std::string s;
    size_t d;
    assert(std::cin >> t >> s >> d);
    std::cout << t << " " << s << " " << d << std::endl;
    size_t n = s.length();
    size_t m = t.length();
    assert(n >= d);
    assert(n >= m);
    std::vector<size_t> approximateOccurrences;
    for (size_t i = 0; i < n - m; ++i) {
        if (HammingDistance(t, s.substr(i, m)) <= d) {
            approximateOccurrences.push_back(i);
        }
    }
    PrintCollection(approximateOccurrences, std::cout);
    PrintCollection(approximateOccurrences, outFile);
    return 0;
}