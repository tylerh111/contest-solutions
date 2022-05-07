#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


bool isspecial(char c) {
    return c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*';
}


bool isSecure(std::string& password) {
    
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    
    bool hasAtLeast8 = 8 <= password.length();
    bool hasAtMost24 = password.length() <= 24;
    
    for(auto& c : password) {
        if (std::islower(c)) hasLower = true;
        if (std::isupper(c)) hasUpper = true;
        if (std::isdigit(c)) hasDigit = true;
        if (isspecial(c)) hasSpecial = true;
    }
    
    
    return hasLower && hasUpper && (hasDigit || hasSpecial) && hasAtLeast8 && hasAtMost24;
}




int main() {
    
    int testcases;
    std::cin >> testcases;
    
    std::string word;
    std::getline(std::cin, word); //skip \n
    for (int i = 0; i < testcases; ++i) {
        std::getline(std::cin, word);
        if (isSecure(word))
            std::cout << word << " - secure.\n";
        else
            std::cout << word << " - not secure.\n";
    }
    
    
    return 0;
}
