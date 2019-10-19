#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>

const int MAXN = 2500;
size_t k;
size_t n;
std::vector<std::string> polymers;
std::vector<std::string> vertices;
std::unordered_map<std::string, int> vertexNum;

std::map<int, std::vector<int>> graph;
std::map<int, int> degIn;
std::map<int, int> degOut;
std::map<std::pair<int, int>, int> edgesCount;
std::vector<bool> used;

std::string currentContig;

bool IsGood(int v) {
    return degIn[v] == 1 && degOut[v] == 1;
}

std::multiset<std::string> contigs;
std::multiset<std::string> answer;

void StartSearch(size_t v) {
    if (used[v]) {
        return;
    }
    for (size_t to : graph[v]) {
        assert(!used[to]);
        currentContig.push_back(vertices[to].back());
        if (IsGood(to)) {
            StartSearch(to);
        } else {
            contigs.insert(currentContig);
        }
        currentContig.pop_back();
    }
}

void PrintSet(const std::multiset<std::string>& s, std::ostream& os = std::cout) {
    bool first = true;
    for (const std::string& elem : s) {
        if (!first) {
            os << " ";
        }
        first = false;
        os << elem;
    }
    os << std::endl;
}

int GetVertexNum(const std::string& v) {
    auto it = vertexNum.find(v);
    if (it == vertexNum.end()) {
        vertexNum[v] = vertices.size();
        vertices.push_back(v);
    }
    return vertexNum[v];
}

void AddEdge(const std::string& a, const std::string& b) {
    int from = GetVertexNum(a);
    int to = GetVertexNum(b);
    graph[from].push_back(to);
    std::cerr << "edge:" << a << " " << b << std::endl;
    degIn[to]++;
    degOut[from]++;
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    for (std::string current; std::cin >> current;) {
        if (current == "Output:") {
            std::cerr << "found output" << std::endl;
            break;
        }
        k = current.length();
        const std::string a = current.substr(0, k - 1);
        const std::string b = current.substr(1, k - 1);
        AddEdge(a, b);
    }
    for (std::string current; std::cin >> current;) {
        answer.insert(std::move(current));
    }
    n = vertices.size();
    used.assign(n, false);
    for (size_t v = 0; v < n; ++v) {
        if (!IsGood(v)) {
            currentContig = vertices[v];
            StartSearch(v);
        }
    }
    std::cout << "canon answer:" << std::endl;
    PrintSet(answer);
    std::cout << "our answer:" << std::endl;
    PrintSet(contigs);
    PrintSet(contigs, outFile);
    if (!answer.empty()) {
        assert(answer == contigs);
    }
    return 0;
}