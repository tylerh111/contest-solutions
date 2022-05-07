#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    
    std::ios_base::sync_with_stdio(false);
    
    unsigned long long m, x, i;
    std::cin >> m;
    
    std::vector<bool> blocks_not_missing(m+1);
    for (i = 0; i < m; ++i) {
        std::cin >> x;
        blocks_not_missing[x-1] = true;
    }
    
    for (i = 0; i < m+1; ++i) {
        if (!blocks_not_missing[i]) {
            std::cout << i+1 << '\n';
            break;
        }
    }
    
    
    return 0;
}
