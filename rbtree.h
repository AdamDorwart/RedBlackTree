#pragma once

#include <iostream>

template<typename T, typename KeyT>
struct RBNode {
    RBNode() {
        isRed = false;
        key = KeyT();
        data = T();
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    
    RBNode(const RBNode& node) {
        copy(node);
    }
    
    ~RBNode() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
    
    RBNode& operator=(const RBNode& node) {
        copy(node);
        return *this;
    }
    
    // Notice that this copy constructors create copys of their subtrees, and leave their parents unconnected.
    void copy(const RBNode& node) {
        isRed = node.isRed;
        key = node.key;
        data = node.data;
        if (node.left) {
            left = new RBNode();
            *left = *(node.left);
            left->parent = this;
        } else {
            left = nullptr;
        }
        if (node.right) {
            right = new RBNode();
            *right = *(node.right);
            right->parent = this;
        } else {
            right = nullptr;
        }
        parent = nullptr;
    }
    
    bool isRed;
    KeyT key;
    T data;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
};

template<typename T, typename KeyT = int>
class RBTree {
    public:
        RBTree() {
            root = nullptr;
        }
        
        RBTree(const RBTree& tree) {
            if (tree.root) {
                *root = *(tree.root);
            }
        }
        
        RBTree& operator=(const RBTree& tree) {
            if (tree.root) {
                *root = *(tree.root);
            }
            return *this;
        }
        
        ~RBTree() {
            if (root) {
                delete root;
            }
        }
        
        RBNode<T, KeyT>* insert(const T& data, const KeyT& key) {
            // Insert node as root
            RBNode<T, KeyT>* newRBNode;
            if (!root) {
                root = new RBNode<T, KeyT>();
                root->key = key;
                root->data = data;
                newRBNode = root;
            }
            return newRBNode;
        }
        
        void remove(RBNode<T, KeyT>* node) {
            
        }
        
        RBNode<T, KeyT>* find(const KeyT& key) {
            
        }
        
    private:
        RBNode<T, KeyT>* root;
        
        void leftRotate(RBNode<T, KeyT>* node) {
            
        }
        
        void rightRotate(RBNode<T, KeyT>* node) {
            
        }
};