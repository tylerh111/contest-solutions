#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>


void solve(std::string& s) {
    
    bool alpha[26] = {0};
    int x;
    
    for (const char& c : s) {
        if (std::isalpha(c)) {
            x = std::tolower(c);
            alpha[x-97] = true;        
        }
    }
    
    bool is_missing = false;
    std::stringstream ss;
    for (int i = 0; i < 26; ++i) {
        if (!alpha[i]) {
            ss << (char) (i+97);
            is_missing = true;
        }
    }
    
    if (!is_missing)
        std::cout << "pangram\n";
    else
        std::cout << "missing " << ss.str() << '\n';
    
}



int main() {
    
    int n;
    std::cin >> n;
    std::cin.ignore();
    
    std::string s;
    
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, s);
        solve(s);
    }
    
    
    
    return 0;
}
