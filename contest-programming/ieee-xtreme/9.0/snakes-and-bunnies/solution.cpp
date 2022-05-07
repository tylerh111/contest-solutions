#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>

void update_warp(std::map<char, std::pair<int, int>>& warps, 
                 char c, int pos) 
{
    auto ret = warps.find(c);
    
    // if warp does not exist then add it
    if (ret == warps.end()) {
        warps.insert({c, {pos, 0}});
    }
    else {
        ret->second.second = pos;
        if (ret->second.first > ret->second.second) {
            int x = ret->second.first;
            ret->second.first = ret->second.second;
            ret->second.second = x;
        }
    }
    
}




void read_board(std::vector<char>& board, 
                std::map<char, std::pair<int, int>>& warps, 
                int n) 
{   
    int x;
    char c;
    
    for (int i = 1; i <= n; i+=2) {
        
        for (int j = 1; j <= n; ++j) {
            x = (n - i)*n + j;
            std::cin >> c;
            board[x] = c;
            if (c != '-')
                update_warp(warps, c, x);
        }
        
        if (i + 1 <= n) {
            for (int j = n; j > 0; --j) {
                x = (n - i - 1)*n + j;
                std::cin >> c;
                board[x] = c;
                if (c != '-')
                    update_warp(warps, c, x);
            }
        }
        
    }
    
    
}



void print_board(std::vector<char>& board, int n) {
    
    int x;
    for (int i = 1; i <= n; i+=2) {
        
        for (int j = 1; j <= n; ++j) {
            x = (n - i)*n + j;
            std::cout << board[x];
        }
        
        std::cout << '\n';
        
        if (i + 1 <= n) {
            for (int j = n; j > 0; --j) {
                x = (n - i - 1)*n + j;
                std::cout << board[x];
            }
        }
        
        std::cout << '\n';
    }
    
}


bool check_warp(std::map<char, std::pair<int, int>>& warps, char c, int moveto) {
    
    if (c == '-') return false;
    
    auto val = warps.find(c)->second;
    if (std::isalpha(c)) {
        if (val.second == moveto) return true;
    }
    else {
        if (val.first == moveto) return true;
    }
    
    return false;
}




bool move(std::vector<char>& board, 
          std::map<char, std::pair<int, int>>& warps, 
          std::vector<int>& board_positions, 
          std::vector<int>& positions, 
          int player, int roll)
{
    int moveto = positions[player] + roll;
    
    std::set<int> moveto_set;
    moveto_set.insert(moveto);
    
    while (board_positions[moveto] != -1 || check_warp(warps, board[moveto], moveto)) {

        // if landed on a token
        while (board_positions[moveto] != -1) {
            moveto++;
            
            // check if place moveto spot has been visited
            if (!moveto_set.insert(moveto).second) return false;
        }

        // if landed on a warp
        while (check_warp(warps, board[moveto], moveto)) {
            auto val = warps.find(board[moveto])->second;
            if (std::isalpha(board[moveto])) {
                if (val.second == moveto)
                    moveto = val.first;
            }
            else {
                if (val.first == moveto)
                    moveto = val.second;
            }
            
            // check if place moveto spot has been visited
            if (!moveto_set.insert(moveto).second) return false;
        }
        
    }
    
    board_positions[positions[player]] = -1;
    board_positions[moveto] = player;
    positions[player] = moveto;
    
    return true;
}



void solve(std::vector<char>& board, 
           std::map<char, std::pair<int, int>>& warps, 
           int n, int m) 
{
    // end conditions
    bool is_winner = false;
    bool is_no_loop = false;
    int loop_winner = -1;
    
    int roll1, roll2;
    int total;
    int player = 0;
    std::vector<int> board_positions(n*n+1, -1);
    std::vector<int> positions(m, 0);
    
    while (!std::cin.eof()) {
        
        total = 0;
        
        // initial move
        std::cin >> roll1;
        total += roll1;
        std::cin >> roll2;
        total += roll2;
        
        is_no_loop = move(board, warps, board_positions, positions, player, total);
        if (!is_no_loop) {
            loop_winner = player + 1;
            break;
        }
        
        // extra move
        if (roll1 == roll2) {
            std::cin >> total;
            
            is_no_loop = move(board, warps, board_positions, positions, player, total);
            if (!is_no_loop) {
                loop_winner = player + 1;
                break;
            }
        }
        
        // check for a winner
        is_winner = std::find(positions.begin(), positions.end(), board.size() - 1) != positions.end();
        if (is_winner)
            break;
        
        player = (player+1) % m;
    }
    
    
    if (is_no_loop) {
        for (const auto& pos : positions)
            std::cout << pos << ' ';
    }
    else {
        std::cout << "PLAYER " << loop_winner << " WINS BY EVIL CYCLE!";
    }
    
    
}





int main() {
    
    int n;
    std::cin >> n;
    
    std::vector<char> board(n*n+1);
    std::map<char, std::pair<int, int>> warps;
    
    read_board(board, warps, n);
    //print_board(board, n);
    
    int m;
    std::cin >> m;
    
    solve(board, warps, n, m);
    
    
    return 0;
}
