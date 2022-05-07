#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

struct node_t {
    int x;
    node_t *left, *right;
};



void fill_tree(node_t*& r) {
    
    std::queue<node_t*> queue;
    
    std::string s;
    std::getline(std::cin, s);
    if (s.compare("-") == 0)
        return;
    
    r = new node_t{std::stoi(s), nullptr, nullptr};
    queue.push(r);
    
    node_t* ptr;
    while(!queue.empty()) {
        ptr = queue.front();
        queue.pop();
        
        if (ptr == nullptr) continue;
        
        //read left
        std::getline(std::cin, s);
        if (s.compare("-") != 0)
            ptr->left = new node_t{std::stoi(s), nullptr, nullptr};
        
        //read right
        std::getline(std::cin, s);
        if (s.compare("-") != 0)
            ptr->right = new node_t{std::stoi(s), nullptr, nullptr};
        
        //push left and right onto queue (in that order)
        queue.push(ptr->left);
        queue.push(ptr->right);
        
    }
    
}


void print_tree(node_t*& r) {
    
    if (r == nullptr) {
        std::cout << "-\n";
        return;
    }
    
    std::cout << r->x << '\n';
    
    print_tree(r->left);
    print_tree(r->right);
}


void delete_tree(node_t*& r) {
    if (r->left != nullptr)
        delete_tree(r->left);
    
    if (r->right != nullptr)
        delete_tree(r->right);
    
    delete r;
}

int main() {
    
    node_t* root = nullptr;
    
    fill_tree(root);
    print_tree(root);
    delete_tree(root);
    
    return 0;
}
