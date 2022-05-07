#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


int main() {
    
    long n, l;
    std::cin >> n >> l;
    
    long n_len, l_len;
    n_len = std::sqrt(n);
    l_len = std::sqrt(l);
    
    long x = 0;
    
    for (long i = 0; i < n_len; ++i)
        for (long j = 0; j < n_len; ++j)
            if (i + l_len <= n_len && j + l_len <= n_len)
                x++;
    
    std::cout << x << '\n';
    
    return 0;
}
