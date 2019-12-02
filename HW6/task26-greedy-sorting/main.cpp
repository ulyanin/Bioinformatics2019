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

void DoSort(std::vector<int> permutation) {
    std::ofstream outFile("answer.txt");
    size_t n = permutation.size();
    PrintContainer(permutation) << std::endl;
    for (size_t i = 0; i < n; ++i) {
        if (permutation[i] == i + 1) {
            continue;
        }
        auto it = std::find_if(
            permutation.begin() + i, permutation.end(),
            [&i] (int elem) {
                return elem == i + 1 || -elem == i + 1;
            });
        assert(it != permutation.end());
        std::reverse(permutation.begin() + i, it + 1);
        for (auto j = permutation.begin() + i; j != it + 1; ++j) {
            (*j) *= -1;
        }
        PrintPermutation(permutation);
//        outFile << "#" << i << " " << it - permutation.begin() << " " << std::endl;
        PrintPermutation(permutation, outFile);
        if (permutation[i] < 0) {
            permutation[i] *= -1;
            PrintPermutation(permutation);
//            outFile << "##" << i << " " << std::endl;
            PrintPermutation(permutation, outFile);
        }
    }
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::vector<int> p = ReadPermutation();
//    PrintContainer(p);
    DoSort(p);

    return 0;
}