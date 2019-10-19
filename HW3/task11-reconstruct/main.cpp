#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

const int MAXN = 2500;
int n;
size_t m;
std::vector<std::string> polymers;
std::string answer;

std::vector<std::vector<int>> graph;
std::vector<int> degIn;

bool IsNext(const std::string& a, const std::string& b) {
    assert(b.length() == n);
    assert(a.length() == n);
    return a.substr(1) == b.substr(0, b.length() - 1);
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    std::cin >> n;
    for (std::string current; std::cin >> current; ) {
        polymers.push_back(std::move(current));
    }
    std::cerr << polymers.size() << std::endl;
    if (polymers.back().length() != polymers.front().length()) {
        answer = polymers.back();
        polymers.pop_back();
    }

    m = polymers.size();
    graph.resize(m);
    degIn.resize(m);
    for (size_t i = 0; i < polymers.size(); ++i) {
        const std::string& a = polymers[i];
        for (size_t j = 0; j < polymers.size(); ++j) {
            const std::string& b = polymers[j];
            if (IsNext(a, b)) {
                graph[i].push_back(j);
                degIn[j]++;
            }
        }
    }
//    for (size_t i = 0; i < m; ++i) {
//        std::cout << graph[i].size() << " " << degIn[i] << std::endl;
//    }
    std::vector<int> starts;
    for (size_t i = 0; i < m; ++i) {
        if (degIn[i] == 0) {
            starts.push_back(i);
        }
    }
    size_t outputSize = n + m - 1;
    if (!answer.empty()) {
        assert(answer.size() == outputSize);
    }
    for (int start : starts) {
        std::vector<int> path;
        std::vector<bool> used(m);
        std::string output = polymers[start];
        for (int current = start; ;) {
            path.push_back(current);
            if (graph[current].empty()) {
                break;
            }
            assert(graph[current].size() == 1);
            int to = graph[current][0];
            if (used[to]) {
                break;
            }
            used[to] = true;
            output.push_back(polymers[to].back());
            current = to;
        }
        if (outputSize == output.size()) {
            std::cout << output << std::endl;
            if (!answer.empty()) {
                std::cout << answer << std::endl;
            }
            outFile << output << std::endl;
        } else {
            std::cout << "Fail" << std::endl;
        }
    }
    return 0;
}