#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>

static const std::unordered_map<char, char> complement {
    {'A', 'T'},
    {'T', 'A'},
    {'C', 'G'},
    {'G', 'C'},
};

static const std::unordered_map<std::string, char> codon2acid = {
    {"GCT", 'A'},
    {"GCC", 'A'},
    {"GCA", 'A'},
    {"GCG", 'A'},

    {"CGT", 'R'},
    {"CGC", 'R'},
    {"CGA", 'R'},
    {"CGG", 'R'},
    {"AGA", 'R'},
    {"AGG", 'R'},

    {"AAT", 'N'},
    {"AAC", 'N'},

    {"GAT", 'D'},
    {"GAC", 'D'},

    {"TGT", 'C'},
    {"TGC", 'C'},

    {"CAA", 'Q'},
    {"CAG", 'Q'},

    {"GAA", 'E'},
    {"GAG", 'E'},

    {"GGT", 'G'},
    {"GGA", 'G'},
    {"GGC", 'G'},
    {"GGG", 'G'},

    {"CAT", 'H'},
    {"CAC", 'H'},

    {"ATT", 'I'},
    {"ATC", 'I'},
    {"ATA", 'I'},

    {"TTA", 'L'},
    {"TTG", 'L'},
    {"CTT", 'L'},
    {"CTC", 'L'},
    {"CTA", 'L'},
    {"CTG", 'L'},

    {"AAA", 'K'},
    {"AAG", 'K'},

    {"ATG", 'M'},

    {"TTT", 'F'},
    {"TTC", 'F'},

    {"CCT", 'P'},
    {"CCA", 'P'},
    {"CCG", 'P'},
    {"CCC", 'P'},

    {"TCT", 'S'},
    {"TCC", 'S'},
    {"TCG", 'S'},
    {"TCA", 'S'},
    {"AGT", 'S'},
    {"AGC", 'S'},

    {"ACT", 'T'},
    {"ACG", 'T'},
    {"ACA", 'T'},
    {"ACC", 'T'},

    {"TGG", 'W'},

    {"TAT", 'Y'},
    {"TAC", 'Y'},

    {"GTT", 'V'},
    {"GTA", 'V'},
    {"GTG", 'V'},
    {"GTC", 'V'},
};

std::string ReverseComplement(std::string pattern) {
    std::reverse(pattern.begin(), pattern.end());
    for (char& c : pattern) {
        c = complement.at(c);
    }
    return pattern;
}

std::string ToPeptide(const std::string& pattern) {
    std::string peptide;
    for (size_t i = 0; i < pattern.size(); i += 3) {
        const std::string codon = pattern.substr(i, 3);
        auto it = codon2acid.find(codon);
        if (it != codon2acid.end()) {
            peptide.push_back(it->second);
        } else {
            peptide.push_back('#');
        }
    }
    return peptide;
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    std::string dna;
    std::string peptide;
    assert(std::cin >> dna >> peptide);
    const size_t patternSize = peptide.size() * 3;
    for (size_t i = 0; i + patternSize < dna.size(); ++i) {
        const std::string pattern = dna.substr(i, patternSize);
        if (ToPeptide(pattern) == peptide || ToPeptide(ReverseComplement(pattern)) == peptide) {
            std::cout << pattern << std::endl;
            outFile << pattern << std::endl;
        }
    }
    return 0;
}