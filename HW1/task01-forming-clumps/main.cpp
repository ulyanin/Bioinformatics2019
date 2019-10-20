#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_set>


std::vector<int> zFunction(std::string_view s) {
    int n = s.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]){
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    z[0] = s.length();
    return z;
}

template <class C>
void PrintCollection(const C& collection, std::ostream& os = std::cout) {
    for (const auto& elem : collection) {
        os << elem << " ";
    }
    os << std::endl;
}


int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    std::string s;
    int k, t;
    size_t L;
    assert(std::cin >> s >> k >> L >> t);
    size_t n = s.length();
    assert(n > L);
    std::unordered_set<std::string> uniqueSubsts;
    for (size_t i = 0; i < n - L; ++i) {
        std::string_view currentClump = std::string_view(s).substr(i, L);
        std::vector<int> z = zFunction(currentClump);
        size_t numberOfSubsts = 0;
        assert(z.size() == L);
        for (int zValue : z) {
            if (zValue >= k) {
                numberOfSubsts++;
            }
        }
        if (numberOfSubsts >= t) {
            uniqueSubsts.insert(s.substr(i, k));
        }
    }
    PrintCollection(uniqueSubsts, std::cout);
    PrintCollection(uniqueSubsts, outFile);
    return 0;
}