#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    
    int n;
    std::cin >> n;
    
    int config[3] = {0,0,0};
    int part_ndx = 0;
    
    std::string part;
    char direction;
    int degree;
    
    for (int i = 0; i < n; ++i) {
        std::cin >> part >> direction >> degree;
        
        if (part.compare("RightArm") == 0) part_ndx = 0;
        if (part.compare("LeftArm") == 0) part_ndx = 1;
        if (part.compare("Base") == 0) part_ndx = 2;
        
        if (direction == 'c') config[part_ndx] = (config[part_ndx] + degree) % 360;
        if (direction == 'C') config[part_ndx] = (config[part_ndx] - degree) % 360;
        
        //std::cout << config[0] << ' ' << config[1] << ' ' << config[2] << '\n';
    }
    
    if (config[0] == 0 && config[1] == 0 && config[2] == 0)
        std::cout << "yes\n";
    else
        std::cout << "no\n";
    
    
    return 0;
}
