#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


int main() {

	int t;
	std::cin >> t;

	double p;
	double x, y;

	for (int i = 0; i < t; i++) {
		std::cin >> p;
		std::cin >> x;
		std::cin >> y;
        
        if (p == 0) {
            std::cout << "Case #" << i + 1 << ": white" << std:: endl;
            continue;
        }
        
        // readjust input
        p = p / 100;
        
		x = x - 50;
		y = y - 50;
        std::swap(x, y);
        
		double endAngle = 2 * M_PI * p ;

		double rhoP = sqrt(x * x + y * y);    //radius to point
		double phiP = atan2(y, x);            //angle to point

        // fix angle to point to be between [0, 2pi]
		while (phiP >= 2 * M_PI)
			phiP -= 2 * M_PI;
		while (phiP < 0)
			phiP += 2 * M_PI;
        

		if (rhoP <= 50 && (0 <= phiP && phiP <= endAngle))
			std::cout << "Case #" << i + 1 << ": black" << std::endl;
		else
			std::cout << "Case #" << i + 1 << ": white" << std::endl;
        
	}

	return 0;
}
