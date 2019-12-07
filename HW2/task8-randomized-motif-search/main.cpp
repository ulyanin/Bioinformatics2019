#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
#include <random>

template <class C>
std::ostream& PrintCollection(const C& collection, std::ostream& os = std::cout, std::string_view delim = " ") {
    for (const auto& elem : collection) {
        os << elem << delim;
    }
    return os;
}

size_t HammingDistance(std::string_view a, std::string_view b) {
    assert(a.length() == b.length());
    size_t dist = 0;
    for (size_t i = 0; i < a.length(); ++i) {
        dist += (a[i] != b[i]);
    }
    return dist;
}

using TProfile = std::unordered_map<char, std::vector<size_t>>;

TProfile DefaultProfile(size_t k) {
    TProfile profile;
    static constexpr std::string_view chars = "ACGT";
    for (const char c : chars) {
        profile[c].assign(k, 0);
    }
    return profile;
}

TProfile CalculateProfile(const std::vector<std::string>& strings) {
    assert(!strings.empty());
    if (strings.empty()) {
        std::cerr << "EMPTY" << std::endl;
        return DefaultProfile(0);
    }
    size_t k = strings[0].length();
    TProfile profile = DefaultProfile(k);
    for (const std::string& s : strings) {
        assert(s.size() == k);
        for (size_t i = 0; i < s.size(); ++i) {
            profile[s[i]][i]++;
        }
    }
    return profile;
}

std::string GetCommonMotif(const TProfile& profile) {
    std::string commonMotif;
    size_t k = profile.at('A').size();
    for (size_t i = 0; i < k; ++i) {
        char bestChar = 'A';
        for (const auto& [c, v] : profile) {
            if (profile.at(bestChar).at(i) < v.at(i)) {
                bestChar = c;
            }
        }
        commonMotif.push_back(bestChar);
    }
    return commonMotif;
}

uint64_t ProbabilityWeight(const std::string& kMer, const TProfile& profile) {
    assert(kMer.length() == profile.at('A').size());
    uint64_t weight = 1;
    for (size_t i = 0; i < kMer.size(); ++i) {
        weight *= profile.at(kMer[i]).at(i) + 1;
    }
    return weight;
}

std::string MostProbableProfile(const std::string& s, const TProfile& profile, size_t k) {
    std::string ans = s.substr(0, k);
    uint64_t bestScore = ProbabilityWeight(ans, profile);
    for (size_t i = 1; i + k < s.size(); ++i) {
        std::string kMer = s.substr(i, k);
        assert(kMer.length() == k);
        size_t probWeight = ProbabilityWeight(kMer, profile);
        if (probWeight > bestScore) {
            bestScore = probWeight;
            ans = kMer;
        }
    }
    return ans;
}


size_t Score(const std::vector<std::string>& motifs) {
    assert(!motifs.empty());
    TProfile profile = CalculateProfile(motifs);
    std::string commonMotif = GetCommonMotif(profile);
    size_t acc = 0;
    for (const std::string& motif : motifs) {
        acc += HammingDistance(motif, commonMotif);
    }
    return acc;
}


std::vector<std::string> RandomizedMotifSearchIteration(const std::vector<std::string>& dna, size_t k) {
    static std::mt19937 gen(42);
    std::uniform_int_distribution<> startChooser(0, dna.front().size() - k);
    std::vector<std::string> bestMotifs;
    for (const std::string& s : dna) {
        size_t start = startChooser(gen);
        bestMotifs.push_back(s.substr(start, k));
        assert(bestMotifs.back().size() == k);
    }
    while (true) {
        const TProfile profile = CalculateProfile(bestMotifs);
        std::vector<std::string> motifs;
        for (const std::string& s : dna) {
            motifs.push_back(MostProbableProfile(s, profile, k));
        }
        if (Score(motifs) < Score(bestMotifs)) {
            bestMotifs = std::move(motifs);
        } else {
            return bestMotifs;
        }
    }

}

std::vector<std::string> RandomizedMotifSearch(const std::vector<std::string>& dna, size_t k, const size_t numIters = 1000) {
    std::vector<std::string> bestMotifs;
    for (size_t i = 0; i < numIters; ++i) {
        std::vector<std::string> motifs = RandomizedMotifSearchIteration(dna, k);
        if (bestMotifs.empty() || Score(motifs) < Score(bestMotifs)) {
            bestMotifs = std::move(motifs);
        }
        std::cout << i << "/" << numIters << " " << Score(bestMotifs) << std::endl;
    }
    assert(!bestMotifs.empty());
    return bestMotifs;
}


int main() {
    assert(freopen("test.txt", "r", stdin));
    std::ofstream outF("ans.txt");
    size_t k, n;
    assert(std::cin >> k >> n);
    std::vector<std::string> dna(n);
    for (size_t i = 0; i < n; ++i) {
        assert(std::cin >> dna[i]);
    }
    std::vector<std::string> motifs = RandomizedMotifSearch(dna, k);
    PrintCollection(motifs, std::cout, "\n");
    PrintCollection(motifs, outF, "\n");
    return 0;
}
