#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


void rotate_left(std::string &s, int d) {
    reverse(s.begin(), s.begin()+d);
    reverse(s.begin()+d, s.end());
    reverse(s.begin(), s.end());
}


void rotate_right(std::string &s, int d) {
   rotate_left(s, s.length()-d);
}

int solve(std::string& input) {
    bool found_k = false;
    
    int n = input.length();
    int i = 1;
    
    for (; i < n; ++i) {
        if (n % i == 0) {
            bool is_i_valid = true;
            std::string perstring = input.substr(0, i);
            
            for (int j = 1; j < n/i; ++j) {
                rotate_right(perstring, 1);
                std::string nexperstring = input.substr(j*i, i);
                
                if (perstring.compare(nexperstring) != 0) {
                    is_i_valid = false;
                    break;
                }
            }
            
            if (is_i_valid) {
                found_k = true;
                break;
            }
            
        }
    }
    
    if (!found_k)
        return n;
    
    return i;
}



int main() {
    
    std::string input;
    std::cin >> input;
    
    int k = solve(input);
    std::cout << k << '\n';
    
    return 0;
}
