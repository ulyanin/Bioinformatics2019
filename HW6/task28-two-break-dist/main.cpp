#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>
#include <sstream>

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
using TGenome = std::vector<std::vector<int>>;

std::ostream& PrintPermutation(const std::vector<int>& p, std::ostream& os = std::cout) {
    os << std::showpos << "(";
    PrintContainer(p, " ", os) << ")";
    return os;
}

std::ostream& PrintGenome(const TGenome& genome, std::ostream& os = std::cout) {
    for (const auto& p : genome) {
        PrintPermutation(p, os);
    }
    os << std::endl;
    return os;
}

std::vector<std::string> SplitBySet(const std::string& s, std::set<char> delims) {
    std::vector<std::string> split;
    std::string current;
    for (char c : s) {
        if (delims.count(c)) {
            if (!current.empty()) {
                split.push_back(std::move(current));
                current.clear();
            }
        } else {
            current.push_back(c);
        }
    }
    if (!current.empty()) {
        split.push_back(std::move(current));
    }
    return split;
}

TGenome ReadGenome() {
    TGenome genome;
    std::string s;
    std::getline(std::cin, s);
    std::vector<std::string> tokens = SplitBySet(s, {'(', ')'});
    for (const std::string& token : tokens) {
        std::stringstream ss(token);
        std::vector<int> p;
        for (int elem; ss >> elem; ) {
            p.push_back(elem);
        }
        genome.push_back(std::move(p));
    }
    return genome;
}

size_t NumberOfSyntenies(const TGenome& genome) {
    size_t s = 0;
    for (const auto& p : genome) {
        s += p.size();
    }
    return s;
}

struct TGraph {
    TGraph(const TGenome& P, const TGenome& Q) {
        N = NumberOfSyntenies(P);
        assert(N == NumberOfSyntenies(Q));
        Nodes = N * 2;
        Graph.resize(Nodes);
        Orientation.assign(N, true);
        FillOrientation(P);
        AddGenome(P);
//        PrintGraph();
        AddGenome(Q);
//        PrintGraph();
    }

    void AddGenome(const TGenome& genome) {
        for (auto p : genome) {
            p.push_back(p.front());
            for (size_t i = 0; i + 1 < p.size(); ++i) {
                size_t node = abs(p[i]) - 1;
                size_t nextNode = abs(p[i + 1]) - 1;
                size_t from = GetEndVertexIndex(node, p[i] > 0);
                size_t to = GetBeginVertexIndex(nextNode, p[i + 1] > 0);
                AddIndirectEdge(from, to);
            }
        }
    }

    void PrintGraph() const {
        for (size_t i = 0; i < Nodes; ++i) {
            std::cout << i << ": ";
            for (size_t to : Graph[i]) {
                std::cout << to << " ";
            }
            std::cout << std::endl;
        }
    }

    void FillOrientation(const TGenome& genome) {
        for (const auto& p : genome) {
            for (int i : p) {
                size_t node = abs(i) - 1;
                Orientation[node] = i > 0;
            }
        }
    }

    size_t GetBeginVertexIndex(size_t node, bool currentOrientation) {
        return node * 2 + ((Orientation[node] ^ currentOrientation) ? 1 : 0);
    }

    size_t GetEndVertexIndex(size_t node, bool currentOrientation) {
        return node * 2 + ((Orientation[node] ^ currentOrientation) ? 0 : 1);
    }


    void AddIndirectEdge(size_t from, size_t to) {
        Graph[from].push_back(to);
        Graph[to].push_back(from);
    }

    size_t NumCycles() {
        Color.assign(Nodes, 0);
        size_t nCycles = 0;
        for (size_t node = 0; node < Nodes; ++node) {
            if (Color[node] == 0) {
                DFS(node);
                nCycles++;
            }
        }
        return nCycles;
    }

    void DFS(size_t v) {
        if (Color[v]) {
            return;
        }
        Color[v] = 1;
        for (size_t to : Graph[v]) {
            DFS(to);
        }
    }

    std::vector<std::vector<size_t>> Graph;
    std::vector<bool> Orientation;
    std::vector<int> Color;
    size_t N = 0;
    size_t Nodes = 0;
};

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    TGenome genomeP = ReadGenome();
    TGenome genomeQ = ReadGenome();
    PrintGenome(genomeP);
    PrintGenome(genomeQ);

//    TGraph ppGraph(genomeP, genomeP);
    TGraph pqGraph(genomeP, genomeQ);
    int blocks = pqGraph.N;
//    int blocks = ppGraph.NumCycles();
    int cycles = pqGraph.NumCycles();
//    std::cout << blocks << std::endl;
//    std::cout << cycles << std::endl;
    std::cout << blocks - cycles << std::endl;
    std::ofstream outFile("answer.txt");
    outFile << blocks - cycles << std::endl;
    return 0;
}