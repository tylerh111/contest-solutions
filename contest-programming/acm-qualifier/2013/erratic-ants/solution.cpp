
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <limits>

int solve(const std::vector<char>& path) {
    

    int len = 0;
    auto pos = std::make_pair(0, 0);
    auto& [x, y] = pos;

    std::map<std::pair<int, int>, int> map;
    map.emplace(pos, len);

    auto traverse = [&](auto dir, bool going_backwards = false) {
        switch (dir) {
            case 'N': if (!going_backwards) y++; else y--; break;
            case 'S': if (!going_backwards) y--; else y++; break;
            case 'E': if (!going_backwards) x++; else x--; break;
            case 'W': if (!going_backwards) x--; else x++; break;
        }
    };

    // calculate best going forwards
    int i = 0;
    for (auto dir : path) {
        std::clog << ++i << ": " << len << ' ';
        traverse(dir);
        len++;
        auto [it, inserted] = map.emplace(pos, len);
        auto& best_len_at_pos = it->second;
        if (!inserted) {
            if (len >= best_len_at_pos)
                len = best_len_at_pos;
            else 
                best_len_at_pos = len;
        }
        std::clog << len << " (" << x << ',' << y << ") " << dir << '\n';
    }
    std::clog << '\n';

    // calculate best going backwards
    for (auto it = rbegin(path); it != rend(path); ++it) {
        std::clog << --i << ": " << len << ' ';
        auto dir = *it;
        traverse(dir, true);
        auto& best_len_at_pos = map.at(pos);
        if (len >= best_len_at_pos) {
            len = best_len_at_pos;
        }
        else {
            ++len;
            best_len_at_pos = len;
        }
        std::clog << len << " (" << x << ',' << y << ") " << dir << '\n';
    }
    std::clog << '\n';

    // calculate best going forwards (again)
    for (auto it = begin(path); it != end(path); ++it) {
        std::clog << ++i << ": " << len << ' ';
        auto dir = *it;
        traverse(dir);
        auto& best_len_at_pos = map.at(pos);
        if (len >= best_len_at_pos) {
            len = best_len_at_pos;
        }
        else {
            ++len;
            best_len_at_pos = len;
        }
        std::clog << len << " (" << x << ',' << y << ") " << dir << '\n';
    }

    return len;
}

int main() {

    int paths;
    std::cin >> paths;

    for (int i = 0; i < paths; ++i) {
        int path_len;
        std::cin >> path_len;

        std::vector<char> path(path_len);
        for (auto& direction : path) {
            std::cin >> direction;
        }

        std::cout << solve(path) << '\n';
    }

}

