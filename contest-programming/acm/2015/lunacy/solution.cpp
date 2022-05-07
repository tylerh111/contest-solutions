#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    
    float in, out;
    std::cin >> in;
    
    while (in != -1) {
        out = 0.167 * in;
        printf("%.2f %.2f\n", in, out);
        std::cin >> in;
    }
    
    
    return 0;
}

