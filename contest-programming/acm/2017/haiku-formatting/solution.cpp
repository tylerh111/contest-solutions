#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>



bool isvowel(char c) {
    c = std::tolower(c);
    return std::isalpha(c) && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y'); 
}


bool isconsonant(char c) {
    c = std::tolower(c);
    return std::isalpha(c) && !isvowel(c);
}

// must input in the order they are seen in the string
bool isconsonant(char c1, char c2) {
    c1 = std::tolower(c1);
    c2 = std::tolower(c2);
    return (c1 == 'q' && c2 == 'u') ||
        (c1 == 'y' && isvowel(c2) && c2 != 'y');
}


int calcSyllables(std::string& word) {
    
    // pointers never point to non alpha characters
    int pcx = 0;  //next next index
    int pcn = -1; //next index
    int pc0 = -2; //current index
    int pc1 = -3; //prev index
    int pc2 = -4; //prev prev index
    int pc3 = -5; //prev prev prev index
    int pc4 = -6;
    
    // finds next available char
    auto getNextCharPtr = [&word](int ptr) {
        //continue incrementing index until it reaches the end or found an alphabetic character
        while(++ptr < word.length() && !std::isalpha(word[ptr]));
        return ptr;
    };
    
    // updates pointers to next alphabetic character index
    auto updatePtrs = [&]() {
        int nn = getNextCharPtr(pcx);
        pc4 = pc3;
        pc3 = pc2;
        pc2 = pc1;
        pc1 = pc0;
        pc0 = pcn;
        pcn = pcx;
        pcx = nn;
    };
    
    updatePtrs();
    updatePtrs();
    
    int syllables = 0;
    
    //similar to pointers
    char cx = 0;
    char cn = 0;
    char c0 = 0;
    char c1 = 0;
    char c2 = 0;
    char c3 = 0;
    char c4 = 0;

    for (; pc0 < word.length(); updatePtrs()) {
        
        if (0 <= pcx && pcx < word.length()) cx = std::tolower(word[pcx]); else cx = 0;
        if (0 <= pcn && pcn < word.length()) cn = std::tolower(word[pcn]); else cn = 0;
        if (0 <= pc0 && pc0 < word.length()) c0 = std::tolower(word[pc0]); else c0 = 0;
        if (0 <= pc1 && pc1 < word.length()) c1 = std::tolower(word[pc1]); else c1 = 0;
        if (0 <= pc2 && pc2 < word.length()) c2 = std::tolower(word[pc2]); else c2 = 0;
        if (0 <= pc3 && pc3 < word.length()) c3 = std::tolower(word[pc3]); else c3 = 0;
        if (0 <= pc4 && pc4 < word.length()) c4 = std::tolower(word[pc4]); else c4 = 0;
        
        //if 'qu' is the current and next characters or
        //if 'y'x is the current and next characters (x is any vowel besides 'y')
        // then skip the 'u' or vowel
        if (isconsonant(c0, cn)) { updatePtrs(); continue; }
        
        
        //if 'le' is the last characters: add 1
        //if 'e'  is the last character: continue
        if (c0 == 'e' && pcn == word.length()) {
            if (c1 == 'l') syllables++; 
            continue; 
        }
        
        
        //if xx'es' is the last characters where xx are two consonants: add 1 and skip
        //if 'es' is the last characters: just skip
        if (c0 == 'e' && cn == 's' && pcx == word.length()) {
            if ((isconsonant(c1) && isconsonant(c2)) || // xx_
                (isconsonant(c1) && isconsonant(c3, c2)) || //qux_
                (isconsonant(c2, c1) && isconsonant(c3)) || //xqu_
                (isconsonant(c2, c1) && isconsonant(c4, c3))) //ququ_
            {
                syllables++;
            }
            updatePtrs();
            continue;
        }
        
        
        if (isvowel(c0) && c1 == 0)             { syllables++; continue; } // first character
        if (isvowel(c0) && isconsonant(c1))     { syllables++; continue; } // x_
        if (isvowel(c0) && isconsonant(c2, c1)) { syllables++; continue; } // xx_
        
    }
    
    return (syllables == 0) ? 1 : syllables;
}



int main() {
    
    std::string line;
    std::getline(std::cin, line);
    std::istringstream buf(line);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> words(beg, end);
    std::vector<int> syllables(words.size());
    
    
    // calculate syllables for all words
    for (int i = 0; i < words.size(); ++i) {
        syllables[i] = calcSyllables(words[i]);
    }
    
    
    
    // organize words into lines
    int numWordsLine1 = 0;
    int numWordsLine2 = 0;
    int numWordsLine3 = 0;
    
    int syllablesLine1 = 0;
    int syllablesLine2 = 0;
    int syllablesLine3 = 0;
    
    int i = 0;
    for (; i < words.size() && syllablesLine1 != 5; ++i) {
        numWordsLine1++;
        syllablesLine1 += syllables[i];
    }
    
    for (; i < words.size() && syllablesLine2 != 7; ++i) {
        numWordsLine2++;
        syllablesLine2 += syllables[i];
    }
    
    for (; i < words.size() && syllablesLine3 != 5; ++i) {
        numWordsLine3++;
        syllablesLine3 += syllables[i];
    }
    
    
//     std::cout << numWordsLine1 << ' ' << numWordsLine2 << ' ' << numWordsLine3 << '\n';
//     std::cout << syllablesLine1 << ' ' << syllablesLine2 << ' ' << syllablesLine3 << '\n';
    
//     for (int i = 0; i < words.size(); ++i) {
//         std::cout << words[i] << ' ' << syllables[i] << '\n';
//     }
    
    
    // print words in correct lines
    // if the syllables do not add up to 17 or not a 5-7-5 pattern print on one line
    if (syllablesLine1 + syllablesLine2 + syllablesLine3 != 17 ||
       syllablesLine1 != 5 || syllablesLine2 != 7 || syllablesLine3 != 5) {
        
        for (auto& word : words) {
            std::cout << word << ' ';
        }
        
    }
    else {
        
        //line 1
        int i = 0;
        for (; i < numWordsLine1; ++i) {
            std::cout << words[i] << ' ';
        }
        
        std::cout << '\n';
        
        //line 2
        for (; i < numWordsLine1 + numWordsLine2; ++i) {
            std::cout << words[i] << ' ';
        }
        
        std::cout << '\n';
        
        //line 3
        for (; i < numWordsLine1 + numWordsLine2 + numWordsLine3; ++i) {
            std::cout << words[i] << ' ';
        }
        
    }
    
    
    
    return 0;
}
