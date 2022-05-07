#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


void readDataset(int numRec, int**& posRec) {
    
    posRec = new int*[numRec];
    
    for (int i = 0; i < numRec; ++i) {
        posRec[i] = new int[4];
        std::cin >> posRec[i][0];
        std::cin >> posRec[i][1];
        std::cin >> posRec[i][2];
        std::cin >> posRec[i][3];
    }
    
}


void deleteDataset(int numRec, int**& posRec) {
    
    for (int i = 0; i < numRec; ++i) {
        delete posRec[i];
    }
    
    delete posRec;
    posRec = nullptr;
}



// check boundaries
bool checkBounds(int x, int b1, int b2) {
    return b1 <= x && x <= b2;
}



int solve(int numRec, int**& posRec) {
    
    int* overlapCtr = new int[numRec];
    for (int i = 0; i < numRec; ++i) {
        overlapCtr[i] = 0;
    }
    
    
    // adjacence matrix
    bool** adjMat = new bool*[numRec];
    for (int i = 0; i < numRec; ++i) {
        adjMat[i] = new bool[numRec];
        for (int j = 0; j < numRec; ++j) {
            adjMat[i][j] = false;
        }
    }
    
    
    for (int i = 0; i < numRec; ++i) {
        
        for (int j = i+1; j < numRec; ++j) {
            
            // don't check rectangles that already overlap
            if (adjMat[i][j]) continue;
            
            // checking if rectangle i intersects with rectangle j
            if ((checkBounds(posRec[j][0], posRec[i][0], posRec[i][2]) && 
                 checkBounds(posRec[j][1], posRec[i][1], posRec[i][3])) ||
                (checkBounds(posRec[j][2], posRec[i][0], posRec[i][2]) && 
                 checkBounds(posRec[j][3], posRec[i][1], posRec[i][3])) ||
                (checkBounds(posRec[j][0], posRec[i][0], posRec[i][2]) && 
                 checkBounds(posRec[j][3], posRec[i][1], posRec[i][3])) ||
                (checkBounds(posRec[j][1], posRec[i][0], posRec[i][2]) && 
                 checkBounds(posRec[j][2], posRec[i][1], posRec[i][3])))
            {
                overlapCtr[i]++;
                overlapCtr[j]++;
                adjMat[i][j] = adjMat[j][i] = true;
            }
            
        }
        
    }
    
    
    int result = 0;
    for (int i = 0; i < numRec; ++i) {
        result = std::max(result, overlapCtr[i]);
    }
    
    
    delete overlapCtr;
    
    return result + 1;
}



int main() {

    int numRec;
    int** posRec = nullptr;
    
    std::cin >> numRec;
    
    int answer;
    
    while (numRec != -1) {
        readDataset(numRec, posRec);
        
        answer = solve(numRec, posRec);
        std::cout << answer << '\n';
        
        deleteDataset(numRec, posRec);
        
        std::cin >> numRec;    
    }
    
    
    
    
    
    return 0;
}

