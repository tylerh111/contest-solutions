#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <unordered_map>
#include <iterator>


unsigned int fact(int n) {
    if (n == 0) return 1;
    return n * fact(n - 1);
}

void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int helper(int data[], int dataSize, int* counter, int nextNdx) {

    if (nextNdx == dataSize - 1) {
        for (int i = 0; i < dataSize; i++) 
            if (*(data + i) == i)
                return 0;
        return (*counter)++;
    }

    for (int i = nextNdx; i < dataSize; i++) {
        swap(data, i, nextNdx);
        helper(data, dataSize, counter, nextNdx + 1);
        swap(data, i, nextNdx);
    }

    return *counter;
}

int countingKeysExhaustive(int data[], int dataSize) {
    if (dataSize == 1) return 0;
    return helper(data, dataSize, new int(0), 0);
}



int main() {

    int n = 0;
    std::cin >> n;
    
    if (n == 1)
        std::cout << "0\n";
    else if (n == 2)
        std::cout << "1\n";
    else {

        unsigned long long* map = new unsigned long long[n + 1];
        
        map[1] = 0;
        map[2] = 1;
        map[3] = 2;
        
        for (int i = 4; i <= n; i++) {
            map[i] = ((i - 1) * (map[i - 1] + map[i - 2])) % 1000000007;
        }

        int output = map[n]; // % 1000000007;
        std::cout << output;
        
    }
    
    
    return 0;
}


