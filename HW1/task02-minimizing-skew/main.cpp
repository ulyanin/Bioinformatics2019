#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_set>
#include <algorithm>


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
    std::cin >> s;
    assert(s.length() > 0);
    size_t n = s.length();
    std::vector<int> balance(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        balance[i + 1] = balance[i];
        if (s[i] == 'C') {
            balance[i + 1]--;
        } else if (s[i] == 'G') {
            balance[i + 1]++;
        }
    }
    int minBalance = *std::min_element(balance.begin(), balance.end());
    std::vector<size_t> minBalancePositions;
    for (size_t i = 1; i <= n; ++i) {
        if (balance[i] == minBalance) {
            minBalancePositions.push_back(i);
        }
    }
    PrintCollection(minBalancePositions);
    PrintCollection(minBalancePositions, outFile);
    return 0;
}