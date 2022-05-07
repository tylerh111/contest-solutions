#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


bool is_valid(int s, int x, int y) {
    
    for (int i = 1; i < s; ++i) {
        int case1 = x*i + y*(i-1);
        int case2 = x*i + y*i;
        
        if (case1 > s && case2 > s)
            break;
        
        if (case1 == s || case2 == s)
            return true;
        
    }
    
    return false;
    
}


void solve(int s) {
    
    std::cout << s << ":\n";
    
    for (int x = 2, y = 1; x < s;) {
        if (is_valid(s, x, y))
            std::cout << x << ',' << y << '\n';
        
        if (x == y) ++x;
        else ++y;
    }
    
}


int main() {
    
    int s;
    std::cin >> s;
    
    solve(s);
    
    return 0;
}
