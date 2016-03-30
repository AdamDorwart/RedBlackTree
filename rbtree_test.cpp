#include <iostream>
#include <iomanip>
#include "rbtree.h"

using namespace std;

using Tree = RBTree<int>;
using Node = RBNode<int, int>;

// Print a BST to stdout
// Inspired by http://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way 
void PostOrderPrint(Node* node, int indent=0) {
    const int indentSize = 5;
    if(node) {
        if(node->left) PostOrderPrint(node->left, indent+indentSize);
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (node->isRed) {
            cout << "{R," << node->key << "}\n ";
        } else {
            cout << "{B," << node->key << "}\n ";
        }
        if(node->right) PostOrderPrint(node->right, indent+indentSize);
    }
}


int main(int argc, char** argv) {
    RBTree<int> tree;
    
    tree.insert(1, 1);
    tree.insert(2, 1);
    tree.insert(3, 1);
    tree.insert(4, 1);
    tree.insert(5, 1);
    tree.insert(6, 1);
    tree.insert(7, 1);
    tree.insert(8, 1);
    tree.insert(9, 1);
    tree.insert(10, 1);
    
    
    PostOrderPrint(tree.getRoot());
    
    return 0;
}