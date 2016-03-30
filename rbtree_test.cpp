#include <iostream>
#include "rbtree.h"

using namespace std;

using Tree = RBTree<int>;
using Node = RBNode<int, int>;

int main(int argc, char** argv) {
    RBTree<int> tree;
    
    Node* root = tree.insert(1, 1);
    
    cout << "Root value: " << root->data << endl;
    
    return 0;
}