#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define L_X_AXIS 100
#define L_Y_AXIS 100
#define A_GRID L_X_AXIS * L_Y_AXIS


struct ellipse {
    double x1, y1, x2, y2, r;
};




inline double calcEllipseArea(ellipse e) {
    return M_PI * (e.r/2) * std::sqrt(std::pow(e.x2-e.x1, 2) + std::pow(e.y2-e.y1, 2) - (e.r*e.r)/4);
}





int solve(std::vector<ellipse>& ellipses) {
    
    double total = 0;
    for (auto e : ellipses) {
        double area = calcEllipseArea(e);
        total += area;
    }
    
    return std::round(100.0 * total / 10000.0);
}






int main() {
    
    std::cout << A_GRID << '\n';
    int numTestcases;
    std::cin >> numTestcases;
    
    
    int numEllipse;
    
    double x1, y1, x2, y2, r; 
    for (int i = 0; i < numTestcases; ++i) {
        
        std::cin >> numEllipse;
        
        std::vector<ellipse> ellipses;
        std::vector<int> ellipseAreas;
        for (int j = 0; j < numEllipse; ++j) {
            std::cin >> x1 >> y1 >> x2 >> y2 >> r;
            ellipse e = {x1, y1, x2, y2, r};
            ellipses.push_back(e);
            ellipseAreas.push_back(calcEllipseArea(e));
        }
        
        
        int result = solve(ellipses);
        std::cout << result << "\%\n";
        
        
    }
    
    
    
    return 0;
}

