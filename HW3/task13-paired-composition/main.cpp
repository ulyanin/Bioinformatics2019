#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>

const int MAXN = 2500;
size_t k;
size_t d;
size_t m;
using TReadPair = std::pair<std::string, std::string>;
std::vector<TReadPair> polymers;
std::string answer;

std::vector<std::vector<int>> graph;
std::vector<int> degIn;


bool IsNext(const std::string& a, const std::string& b) {
    return a.substr(1) == b.substr(0, b.length() - 1);
}

bool IsNext(const TReadPair& a, const TReadPair& b) {
    return IsNext(a.first, b.first) && IsNext(a.second, b.second);
}

void DoCopy(std::string& s, size_t pos, std::string_view toCopy) {
    for (size_t i = 0; i < toCopy.length(); ++i,++pos) {
        if (s[pos] != '-') {
            assert(s[pos] == toCopy[i]);
        }
        s[pos] = toCopy[i];
    }
}

void ApplyReadPair(std::string& s, size_t pos, const TReadPair& p) {
    assert(pos + 2 * k + d <= s.size());
//    assert(std::string_view(s).substr(pos, k) == p.first);
//    assert(std::string_view(s).substr(pos + k + d, k) == p.second);
    DoCopy(s, pos, p.first);
    DoCopy(s, pos + k + d, p.second);
//    std::copy(p.first.begin(), p.first.end(), s.begin() + pos);
//    std::copy(p.second.begin(), p.second.end(), s.begin() + pos + k + d);
}

int main() {
#ifdef ULYANIN
    freopen("test.txt", "r", stdin);
#endif
    std::ofstream outFile("answer.txt");
    std::cin >> k >> d;
    for (std::string current; std::cin >> current; ) {
        if (current.length() != 2 * k + 1) {
            answer = current;
            break;
        }
        assert(current.length() == 2 * k + 1);
        std::string a = current.substr(0, k);
        std::string b = current.substr(k + 1);
        assert(b.length() == k);
        polymers.emplace_back(a, b);
    }
    std::cerr << polymers.size() << std::endl;
    m = polymers.size();
    graph.resize(m);
    degIn.resize(m);
    for (size_t i = 0; i < polymers.size(); ++i) {
        const TReadPair& a = polymers[i];
        for (size_t j = 0; j < polymers.size(); ++j) {
            const TReadPair& b = polymers[j];
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
    size_t outputSize = k * 2 + d + m - 1;
    if (!answer.empty()) {
        std::cerr << answer.size() << " " << outputSize << std::endl;
        assert(answer.size() == outputSize);
    }
    for (int start : starts) {
        std::vector<bool> used(m);
        std::string output(outputSize, '-');
        ApplyReadPair(output, 0, polymers[start]);
        used[start] = true;
        for (int current = start, pos = 0; ;) {
//            std::cerr << output << std::endl;

            if (graph[current].empty()) {
                break;
            }
            assert(graph[current].size() == 1);
            int to = graph[current][0];
            assert(IsNext(polymers[current], polymers[to]));
            if (used[to]) {
                break;
            }
            used[to] = true;
            ++pos;
            ApplyReadPair(output, pos, polymers[to]);
            current = to;
        }
        if (std::count(output.begin(), output.end(), '-') == 0) {
            std::cout << output << std::endl;
            if (!answer.empty()) {
                std::cout << answer << std::endl;
                assert(answer.size() == output.size());
                assert(answer == output);
            }
            outFile << output << std::endl;
        } else {
            std::cout << "Fail" << std::endl;
        }
    }
    return 0;
}