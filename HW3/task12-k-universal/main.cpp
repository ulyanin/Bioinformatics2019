#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <cstring>

bool GetBit(uint32_t n, uint32_t i) {
    return n & (1u << i);
}

uint32_t SetBit(uint32_t n, uint32_t i) {
    return n | (1u << i);
}

template<class T>
std::string ToBinary(T num, uint32_t n) {
    std::string ans(n, '-');
    for (uint32_t i = 0; i < n; ++i) {
        ans[n - i - 1] = '0' + GetBit(num, i);
    }
    return ans;
}

const size_t MAXN = 10;
std::vector<std::vector<int>> graph;
bool dp[MAXN][1u << MAXN];
int parent[MAXN][1u << MAXN];

bool Match(int a, int b, uint32_t k) {
    std::string aBin = ToBinary(a, k);
    std::string bBin = ToBinary(b, k);
    return aBin.substr(1) == bBin.substr(0, bBin.length() - 1);
}



std::string FindDeBreijnSeq(uint32_t n) {
    std::vector<bool> used(1 << n, false);
    uint32_t start = 0;
    std::string ans = ToBinary(start, n);
    used[start] = true;
    uint32_t current = start;
    for (uint32_t i = n; i < (1u << n); ++i) {
//        std::cerr << i << " " << ans << std::endl;
        uint32_t last = current;
        bool any = false;
        for (uint32_t bit = 1; bit != -1; --bit) {
            current = ((last << 1u) & ~(1u << n)) | (bit);
//            std::cerr << ToBinary(last, n + 2) << " " << ToBinary(current, n + 2) << " " << bit;
            if (!used[current]) {
//                std::cerr << current << std::endl;
                used.at(current) = true;
                any = true;
                ans.push_back('0' + bit);
                break;
            }
        }
        assert(any);
    }
//    assert(ans.back() == ans.front());
    return ans;
}

int main() {
#ifdef ULYANIN
    freopen("sample.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    uint32_t n;
    std::cin >> n;
    std::string ans = FindDeBreijnSeq(n);
    std::cout << ans << std::endl;
    outFile << ans << std::endl;
    return 0;
}