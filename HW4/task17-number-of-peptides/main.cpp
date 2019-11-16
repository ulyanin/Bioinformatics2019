#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>


static std::vector<int32_t> weights = {
    57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186,
};


int64_t CalcNumberOfLinearPeptides(int32_t weight) {
    std::vector<int64_t> dp(weight + 200);
    dp[0] = 1;
    for (int32_t w = 0; w <= weight; ++w) {
        for (int32_t wItem : weights) {
            dp[w + wItem] += dp[w];
        }
    }
    return dp[weight];
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    size_t peptideWeight;
    assert(std::cin >> peptideWeight);
    int64_t numberOfPeptides = CalcNumberOfLinearPeptides(peptideWeight);
    std::cout << numberOfPeptides << std::endl;
    outFile << numberOfPeptides << std::endl;
    return 0;
}