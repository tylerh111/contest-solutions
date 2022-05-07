#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


int solve(long x) {
    if (x == 1) return 2;
    return solve(std::log10(x) + 1) + 1;
}


int main() {
    
    long x;
    std::string input;
    std::cin >> input;
    
    while (input.compare("END") != 0) {
        
        x = input.length();
        
        if (x == 1 && input.compare("1") == 0)
            std::cout << "1\n";
        else
            std::cout << solve(x) << '\n';
        
        std::cin >> input;
    }
    
    return 0;
}
