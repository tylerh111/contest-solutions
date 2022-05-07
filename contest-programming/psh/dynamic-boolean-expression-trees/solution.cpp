#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


struct node {
    char data;
    node* left;
    node* right;
};



node* build_tree() {
    
    char in;
    std::cin >> in;
    
    node* ret = new node();
    ret->data = in;
    
    switch(in) {
        case '!':
            ret->left = build_tree();
            ret->right = nullptr;
            break;
        case '^':
        case '|':
        case '&':
            ret->left = build_tree();
            ret->right = build_tree();
            break;
        case 't':
        case 'f':
            ret->left = nullptr;
            ret->right = nullptr;
            break;
        default:
            std::cout << "error: in = " << in << std::endl;
            break;
    }
    
    return ret;
}


void modify_tree(node* root, std::string path, char mod) {
    
    node* ptr = root;
    
    for (char const& c : path) {
        if (c == 'l') {
            ptr = ptr->left;
        }
        else if (c == 'r') {
            ptr = ptr->right;
        }
        else {
            std::cout << "error: direction = " << c << std::endl;
        }
    }
    
    ptr->data = mod;
}


bool evaluate_tree(node* root) {
    
    switch (root->data) {
        case '^':
            return evaluate_tree(root->left) ^ evaluate_tree(root->right);
        case '|':
            return evaluate_tree(root->left) | evaluate_tree(root->right);
        case '&':
            return evaluate_tree(root->left) & evaluate_tree(root->right);
        case '!':
            return !evaluate_tree(root->left);
        case 't':
            return true;
        case 'f':
            return false;
        default:
            std::cout << "error: data = " << root->data << std::endl;
            break;
    }
    
    return false;
}





int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int x, y;
    std::cin >> x;
    std::cin >> y;
    
    node* root = build_tree();
    
    for (int i = 0; i < y; ++i) {
        std::string operation;
        std::cin >> operation;
        
        if (operation == "mod") {
            std::string path;
            char mod;
            std::cin >> path;
            std::cin >> mod;
            modify_tree(root, path, mod);
        }
        else if (operation == "eval") {
            if (evaluate_tree(root))
                std::cout << "t\n";
            else
                std::cout << "f\n";
        }
        else {
            std::cout << "error: operation = " << operation << std::endl;
        }
        
    }
    

    
    delete root;
    
    return 0;
}