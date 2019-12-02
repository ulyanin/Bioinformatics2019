#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <unordered_set>

template <class C>
void PrintCollection(const C& collection, std::ostream& os = std::cout, std::string_view delimiter = " ") {
    for (const auto& elem : collection) {
        os << elem << delimiter;
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

size_t NumOfOccurrencesWithUpToDMismatches(std::string_view s, std::string_view t, size_t d) {
    assert(s.size() >= t.size());
    size_t occurrences = 0;
    for (size_t i = 0; i + t.size() < s.size(); ++i) {
        std::string_view current = s.substr(i, t.size());
        if (HammingDistance(current, t) <= d) {
            occurrences++;
        }
    }
    return occurrences;
}


struct TKMersGenerator {
    std::string Polymer = "";
    static constexpr std::string_view Alphabet = "ATGC";
    std::unordered_map<size_t, std::vector<std::string>> Occurrences;
    size_t MaxOccurrences = 0;

    void Gen(size_t pos, size_t k, const std::string& s, size_t d) {
        if (pos == k) {
            size_t nOccurrences = NumOfOccurrencesWithUpToDMismatches(s, Polymer, d);
            if (nOccurrences >= MaxOccurrences) {
                MaxOccurrences = nOccurrences;
                Occurrences[nOccurrences].push_back(Polymer);
            }
            return;
        }
        for (char c : Alphabet) {
            Polymer.push_back(c);
            Gen(pos + 1, k, s, d);
            Polymer.pop_back();
        }
    }
};


int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    std::string s;
    size_t d, k;
    assert(std::cin >> s >> k >> d);
    TKMersGenerator gen;
    gen.Gen(0, k, s, d);
    std::cout << "Max = " << gen.MaxOccurrences << std::endl;
    const std::vector<std::string>& occurrences = gen.Occurrences.at(gen.MaxOccurrences);
    PrintCollection(occurrences);

    return 0;
}