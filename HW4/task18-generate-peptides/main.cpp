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

std::vector<int> CyclicSpectrum(const std::vector<int>& peptide) {
    std::vector<int> cyclicPeptide = peptide;
    cyclicPeptide.insert(cyclicPeptide.end(), peptide.begin(), peptide.end());
    std::vector<int> spectrum = {0};
    for (size_t start = 0; start < peptide.size(); ++start) {
        int sum = 0;
        for (size_t end = start; end < start + peptide.size(); ++end) {
            if (start != 0 && start + peptide.size() == end + 1) {
                break;
            }
            sum += cyclicPeptide[end];
            spectrum.push_back(sum);
        }
    }
    std::sort(spectrum.begin(), spectrum.end());
    return spectrum;
}

std::vector<int> NonCyclicSpectrum(const std::vector<int>& peptide) {
    std::vector<int> spectrum = {0};
    for (size_t start = 0; start < peptide.size(); ++start) {
        int sum = 0;
        for (size_t end = start; end < peptide.size(); ++end) {
            sum += peptide[end];
            spectrum.push_back(sum);
        }
    }
    std::sort(spectrum.begin(), spectrum.end());
    return spectrum;
}

template <class C>
bool Includes(C c1, C c2) {
    return std::includes(c1.begin(), c1.end(), c2.begin(), c2.end());
}

std::vector<int> generated;
std::ofstream outFile;

void BranchAndBound(int generatedSum, const std::vector<int>& experimentalSpectrum) {
    assert(!experimentalSpectrum.empty());
//    std::cout << "!!! ";
//    PrintContainer(generated);
    const std::vector<int> generatedNonCyclicSpectrum = NonCyclicSpectrum(generated);
    if (generatedSum > experimentalSpectrum.back() || !Includes(experimentalSpectrum, generatedNonCyclicSpectrum)) {
        return;
    }

    const std::vector<int> generatedCyclicSpectrum = CyclicSpectrum(generated);
    if (generatedSum == experimentalSpectrum.back() && generatedCyclicSpectrum == experimentalSpectrum) {
        PrintContainer(generated, "-") << " ";
        PrintContainer(generated, "-", outFile) << " ";
        return;
    }
    for (int w : weights) {
        generated.push_back(w);
        BranchAndBound(generatedSum + w, experimentalSpectrum);
        generated.pop_back();
    }
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    outFile.open("answer.txt");
    std::vector<int> experimentalSpectrum;
    for (int s; std::cin >> s; ) {
        experimentalSpectrum.push_back(s);
    }
    BranchAndBound(0, experimentalSpectrum);
//    auto s = NonCyclicSpectrum({1,3, 6, 10, 11});
//    PrintContainer(s);

    return 0;
}