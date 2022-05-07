#include <cmath>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>


// does x divide n
bool isdivisor(uint64_t n, uint64_t x) {
    return n%x == 0;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    uint64_t n, f;
    std::cin >> n >> f;
    
    std::vector<uint64_t> unfriendlies(n);
    
    for (uint64_t i = 0; i < n; ++i) {
        std::cin >> unfriendlies[i];
    }
    
    
    uint32_t counter = 0;
    for (uint64_t i = 2; i <= f; ++i) {
        if (!isdivisor(f, i)) continue;
        
        bool isvalid = true;
        
        for (auto it = unfriendlies.rbegin(); it != unfriendlies.rend(); ++it) {
            if (isdivisor(*it, i)) {
                isvalid = false;
                break;
            }
        }
        
        if (isvalid) counter++;
    }
    
    std::cout << counter << '\n';
    
    return 0;
}

