#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

struct Person {
    int height;
    int level;
    Person* blocker;
    std::vector<Person*> blocking;
    
    ~Person() {
        for (auto& p : blocking) {
            delete p;
            p = nullptr;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        
        os << std::string(p.level, '-') << p.height << '\n';
        for (const auto& per : p.blocking) {
            os << *per;
        }
        return os;
    }
    
};




int convertHeight(int feet, int inches) {
    return feet*12 + inches;
}

int readHeight() {
    std::string name;
    int f,i;
    std::cin >> name >> f >> i;
    return convertHeight(f, i);
}


Person* findBlocker(Person* infront, int h) {
    Person* b = infront;
    
    // continue moving up the tree until we find someone that is taller than h
    while (b->level != 0 && b->height <= h) {
        b = b->blocker;
    }
    
    return b;
}


int solve(Person* root) {
    int aggravation = root->level * root->blocking.size();
    
    for (const auto& p : root->blocking) {
        aggravation += solve(p);
    }
    
    return aggravation;
}




int main() {
    
    int n;
    std::cin >> n;
    
    Person root = {0, 0, nullptr, {}};
    Person* infront = &root;
    
    for (int i = 0; i < n; ++i) {
        int h = readHeight();
        Person* blocker = findBlocker(infront, h);
        
        Person* p = new Person();
        *p = {h, blocker->level+1, blocker, {}};
        
        blocker->blocking.push_back(p);
        infront = p;
    }
    
    // std::cout << root << std::endl;
    int aggravation_level = solve(&root);
    std::cout << aggravation_level << std::endl;
    
    return 0;
}
