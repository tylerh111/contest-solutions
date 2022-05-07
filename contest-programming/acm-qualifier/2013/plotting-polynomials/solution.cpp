#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>



void createPascals(int len, int**& triangle) {
    triangle = new int*[len];
    for (int i = 0; i < len; ++i) {
        triangle[i] = new int[len];
    }
    
    for (int x = 0; x < len; ++x) {
        for (int j = 0; j <= x; ++j) {
            int i = x - j;
            if (i == 0 || j == 0) {
                triangle[i][j] = 1;
            }
            else {
                triangle[i][j] = triangle[i-1][j] + triangle[i][j-1];
            }
        }
    }
    
}


void deletePascals(int len, int**& triangle) {
    for (int i = 0; i < len; ++i) {
        delete triangle[i];
    }
    delete triangle;
    triangle = nullptr;
}



long calcPoly(int len, int*& poly, int x) {
    long p = 0;
    for (int j = 0; j < len; ++j) {
        p += poly[len-j-1] * std::pow(x, j);
    }
    return p;
}


long calcPascals(int len, int**& tri, int x, long*& c) {
    
    long result = 0;
    for (int j = 0; j <= x; ++j) {
        int i = x - j;
        result += static_cast<long>(tri[i][j]) * c[j+1];
    }
    
    return result;
}


void solve(int len, int*& poly, int**& tri) {
    
    //C
    long* c = new long[len]; 
    
    //C_0
    c[0] = poly[len-1];
    std::cout << c[0] << ' ';
    
    //C_1
    long p_i_1 = calcPoly(len, poly, 1); 
    c[1] = p_i_1 - c[0];
    std::cout << c[1] << ' ';
    
    //C_i
    long p_i;
    long c_i_prime;
    for (int i = 2; i < len; ++i) {
        
        //p_i
        p_i = calcPoly(len, poly, i);
        
        //c_i_prime
        c_i_prime = calcPascals(len, tri, i-1, c);
        
        c[i] = p_i - p_i_1 - c_i_prime;
        std::cout << c[i] << ' ';
        
        p_i_1 = p_i;
    }
    
    delete c;
}





int main() {
    
    int degree;
    int len;
    int* polynomial = nullptr;
    std::cin >> degree;
    len = degree+1;
    polynomial = new int[len];
    for (int i = 0; i < len; ++i) {
        std::cin >> polynomial[i];
    }
    
    int** triangle = nullptr;
    createPascals(len, triangle);
    
    
    solve(len, polynomial, triangle);
    
    
    deletePascals(len, triangle);
    
    return 0;
}

