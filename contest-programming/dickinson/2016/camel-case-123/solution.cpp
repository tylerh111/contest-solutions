#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>


void cammelCasize(std::vector<std::string>& words) {
    
    //i: index for word
    //j: index for new_word
    unsigned long i, j;
    
    for (auto& word : words) {
        
        // if word is exactly "_" or word does not contain a '_'
        // then skip word
        if (word.compare("_") == 0) continue;
        if (word.find('_') == std::string::npos) continue;
        
        char* new_word = new char[word.length()];
        
        for (i = 0, j = 0; i < word.length(); ++i) {
            
            //if the first or last letter is an '_'
            if (i == 0 && word[i] == '_') continue;
            if (i == word.length()-1 && word[i] == '_') continue;
            
            if (word[i] == '_') {
                word[i+1] = std::toupper(word[i+1]);
                ++i; // skip '_'
            }
            else
                word[i] = std::tolower(word[i]);
            
            new_word[j] = word[i];
            ++j;
        }
        
        word = std::string(new_word, j);
    }
    
    
}




int main() {

    
    while (!std::cin.eof()) {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream buf(line);
        std::istream_iterator<std::string> beg(buf), end;

        std::vector<std::string> words(beg, end);

        cammelCasize(words);
        
        for (const auto& w : words) {
            std::cout << w << ' ';
        }
        
        if (!std::cin.eof())
            std::cout << '\n';
        
    }
        
        
    return 0;
}
