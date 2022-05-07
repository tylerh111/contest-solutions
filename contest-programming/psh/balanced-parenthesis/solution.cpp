
#include <iostream>
#include <set>
#include <string>

std::set<std::string> solve(int n) {

    if (n == 0) return {""};

    std::set<std::string> ret;
    auto set = solve(n-1);
    for (auto& s : set) {
        auto tmp = "(" + s;
        for (int i = 1; i <= tmp.size(); ++i) {
            auto new_str = tmp.substr(0, i) + ")" + tmp.substr(i);
            auto [it, inserted] = ret.emplace(new_str);
            if (!inserted) break;
        }
    }

    return ret;
}

int main() {

    int n;
    std::cin >> n;

    auto solutions = solve(n);
    for (auto& str : solutions) {
        std::cout << str << '\n';
    }
}
