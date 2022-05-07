#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

bool ismultiple(int a, int b) {
    return a%b == 0;
}


int solve(int a, int b, int c, int d) {
    
    bool ismult_a;
    bool ismult_b;
    bool whammy = false;
    int i;
    for (i = 1; i <= d; ++i) {
        
        // if multiple of c  OR (not a multiple of a during a whammy)
        if ((!(ismult_a = ismultiple(i, a)) && whammy) || ismultiple(i, c)) {
            whammy = true;
            std::cout << "Whammy\n";
        }
        // if not the first condition AND (multiple of a OR multiple of b)
        else if (ismult_a | (ismult_b = ismultiple(i, b))) {
            if (ismult_a) {
                std::cout << "Fizz";
                whammy = false;
            }

            if (ismult_b && !whammy)
                std::cout << "Buzz";
            
            std::cout << '\n';
        }
        // if not a multiple of a or b or c and not during a whammy
        else {
            std::cout << i << '\n';
        }
        
    }
    
    return i;
}



int readInput(int& a, int& b, int& c, int& d) {
    
    std::cin >> a; std::cin.ignore();
    if (a == -1) return 1;
    
    std::cin >> b; std::cin.ignore();
    std::cin >> c; std::cin.ignore();
    std::cin >> d; std::cin.ignore();
    
    return 4;
}




int main() {
    
    
    int a, b, c, d;
    
    //exit loop when a is -1
    while (true) 
    {
        
        readInput(a, b, c, d);
        if (a == -1) break;
        
        //std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
        
        solve(a, b, c, d);
        std::cout << "Done\n";
        
    }
    
    return 0;
}
