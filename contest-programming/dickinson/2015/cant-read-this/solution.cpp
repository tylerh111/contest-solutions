#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

bool readInput(std::stringstream& ss) {
    std::string buf;
    std::getline(std::cin, buf);
    
    if (buf.empty()) return false;
    ss << buf;
    return true;
}


void solve(std::string& in) {
    
    char* out = new char[in.length() + 1];
    out[in.length()] = '\0';
    
    unsigned long int i;
    unsigned long int j = 0;
    
    //fill even
    for (i = 0; j < in.length() && i < in.length(); ++j, i+=2) {
        char c = in[j];
        if (c == '*')
            out[i] = '\n';
        else
            out[i] = c;
        
    }
    
    
    //fill odd
    for (i = 1; j < in.length() && i < in.length(); ++j, i+=2) {
        char c = in[j];
        if (c == '*')
            out[i] = '\n';
        else
            out[i] = c;
        
    }
    
    std::string s(out);
    std::cout << s;
    delete out;
}




int main() {
    
    std::stringstream ss;
    
    while(readInput(ss));
    
    std::string buf(ss.str());
    ss.clear();
    solve(buf);
    
    
    return 0;
}
