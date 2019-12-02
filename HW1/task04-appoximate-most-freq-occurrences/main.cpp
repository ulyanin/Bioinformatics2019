#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
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
    std::string s;
    size_t d, k;
    assert(std::cin >> s >> k >> d);
    size_t n = s.length();
    std::vector<size_t> approxOccurreces(n, 0);
    for (size_t i = 0; i < n - k; ++i) {
        for (size_t j = 0; j < n - k; ++j) {
            if (HammingDistance(std::string_view(s).substr(i, k), std::string_view(s).substr(j, k)) <= d) {
                approxOccurreces[i]++;
            }
        }
    }
    size_t maxOccurences = *std::max_element(approxOccurreces.begin(), approxOccurreces.end());
    std::vector<std::string_view> mostFreqAppoxOccurrences;
    for (size_t i = 0; i < n; ++i) {
        if (approxOccurreces[i] == maxOccurences) {
            mostFreqAppoxOccurrences.push_back(std::string_view(s).substr(i, k));
        }
    }
    PrintCollection(mostFreqAppoxOccurrences, std::cout);
    PrintCollection(mostFreqAppoxOccurrences, outFile);
    return 0;
}