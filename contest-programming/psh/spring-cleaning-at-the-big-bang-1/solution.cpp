#include <cstdint>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

uint64_t factorial(uint64_t x, std::vector<uint64_t>& factorials) {
    if (x == 0) return factorials[0] = 1;
    return factorials[x] = x * factorial(x-1, factorials);
}


uint64_t nchoosek(int n, int k, std::vector<uint64_t>& factorials) {
    return factorials[n] / (factorials[k] * factorials[n-k]);
}


void printvec(std::vector<uint64_t>& v) {
    for (const auto& x : v)
        std::cout << x << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    std::vector<uint64_t> factorials(n+1);
    factorial((uint64_t) n, factorials); // init vector
    
    uint64_t counter = 0;
    uint64_t tmp;
    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        counter += tmp;
    }
    
    for (int k = 2; k <= n; ++k) {
        uint64_t extras = nchoosek(n, k, factorials);
        for (uint64_t i = 0; i < extras; ++i) {
            std::cin >> tmp;
            if (k%2 == 0) counter -= tmp;
            else counter += tmp;
        }
    }
    
    std::cout << counter << '\n';
    
    return 0;
}
