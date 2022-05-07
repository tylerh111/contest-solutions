#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include "bits/stdc++.h" 


/**
 * Solution from:
 * https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/
 **/


// C++ program to find prime factorization of a
// number n in O(Log n) time with precomputation
// allowed.
#define MAXN 10000001


// stores smallest prime factor for every number
long spf[MAXN];
int excess[MAXN];


// Calculating SPF (Smallest Prime Factor) for every
// number till MAXN.
// Time Complexity : O(nloglogn)
void fillSPF() {
    
    spf[1] = 1;
    excess[1] = -1;
    
    // mark spf for all odd numbers as itself
    // mark spf for all even numbers as 2
    for (long i = 2; i < MAXN; ++i) {
        excess[i] = -1;
        spf[i] = (i%2 == 0) ? 2 : i;
    }

    for (long i = 3; i*i < MAXN; ++i) {
        
        // checking if i is prime
        if (spf[i] == i) {
            
            // marking SPF for all numbers divisible by i
            for (long j = i*i; j < MAXN; j+=i) {
                // marking spf[j] if it is not previously marked
                if (spf[j]==j) spf[j] = i;
            }
        }
        
    }
    
}



// A O(log n) function returning primefactorization
// by dividing by smallest prime factor at every step
std::vector<long> getFactorization(long x)
{
    std::vector<long> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    
    return ret;
}






int calcExcess(long x) {
    std::vector<long> factors = getFactorization(x);
    int excess = 0;
    long prevFactor = 0;
    for (long factor : factors) {
        if (prevFactor == factor) {
            excess++;
        }
        prevFactor = factor;
    }
    
    return excess;
}








int solve(long n0, long n1) {
    
    long maxN = 0;
    int maxExcess = -1;
        
    for (long x = n0; x <= n1; ++x) {
        
        if (excess[x] == -1) {
            excess[x] = calcExcess(x);
        }
        
        if (excess[x] > maxExcess) {
            maxExcess = excess[x];
            maxN = x;
        }
    }
    
    return maxN;
}



int main() {
    
    // precalculating Smallest Prime Factor 
    fillSPF();
    
    long n0, n1;
    int result;
    
    //read input
    std::cin >> n0 >> n1;
    while (n0 != 0 && n1 != 0) {
        
        //solve
        result = solve(n0, n1);
        
        //write output
        std::cout << result << '\n';
    
        //read input
        std::cin >> n0 >> n1;
    }
    
    return 0;
}
