#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>


struct game_t {
    std::string t1, t2;
    int s1, s2;
};

void readGame(std::vector<game_t>& games, std::map<std::string, int>& teams) {
    std::pair<std::map<std::string, int>::iterator, bool> ret;
    int i = 0;
    while(true) {
        game_t g;
        std::cin >> g.t1;
        if (g.t1.empty()) break;
        std::cin >> g.s1 >> g.t2 >> g.s2;
        ret = teams.insert(std::pair<std::string, int>(g.t1, i));
        if (ret.second) ++i;
        ret = teams.insert(std::pair<std::string, int>(g.t2, i));
        if (ret.second) ++i;
        games.push_back(g);
    }
}


void print_games_teams(std::vector<game_t>& games, std::map<std::string, int>& teams) {
    for (const auto& g : games) {
        std::cout << g.t1 << ' ' << g.s1 << ' ' << g.t2 << ' ' << g.s2 << '\n';
    }
    
    std::cout << '\n';
    
    for (const auto& t : teams) {
        std::cout << t.second << ':' << t.first << '\n';
    }
}


void solve(std::vector<game_t>& games, std::map<std::string, int>& teams) {
    
    std::vector<int> losses(teams.size());
    std::pair<std::string, int> p;
    
    for (const auto& g : games) {
        if (g.s1 < g.s2) losses[teams.find(g.t1)->second]++;
        if (g.s1 > g.s2) losses[teams.find(g.t2)->second]++;
    }
    
    for (const auto& t : teams) {
        if (losses[t.second] == 0)
            std::cout << t.first << '\n';
    }
    
}



int main() {
    
    game_t g{};
    std::vector<game_t> games;
    std::map<std::string, int> teams;
    
    readGame(games, teams);
    solve(games, teams);
    
    return 0;
}
