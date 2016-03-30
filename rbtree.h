#pragma once

#include <iostream>

template<typename T, typename KeyT>
struct RBNode {
    RBNode() {
        isRed = true;
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
        
        RBNode<T, KeyT>* insert(const KeyT& key, const T& data) {
            RBNode<T, KeyT>* newRBNode;
            
            if (!root) {
                // Insert node as root
                root = new RBNode<T, KeyT>();
                root->key = key;
                root->data = data;
                root->isRed = false;
                newRBNode = root;
            } else {
                // Traverse Tree (DFS)
                RBNode<T, KeyT> *curNode, *parentNode, **nextNode;
                curNode = root;
                bool locationFound = false;
                while (!locationFound) {
                    if (key < curNode->key) {
                        // Key is less : Go left
                        parentNode = curNode;
                        nextNode = &(curNode->left);
                    } else if (curNode->key < key) {
                        // Key is more : Go right
                        parentNode = curNode;
                        nextNode = &(curNode->right);
                    } else {
                        // Key is equal : Replace Data
                        curNode->data = data;
                        locationFound = true;
                    }
                    
                    if (!*nextNode) {
                        // No next node : Insert new node here
                        *nextNode = new RBNode<T, KeyT>();
                        curNode = *(nextNode);
                        curNode->key = key;
                        curNode->data = data;
                        curNode->parent = parentNode;
                        locationFound = true;
                    }
                    
                    curNode = *(nextNode);
                }
                
                // Rebalance Tree
                while (curNode != root) {
                    RBNode<T, KeyT>* parent = curNode->parent;
                    if (parent->isRed) {
                        RBNode<T, KeyT>* gparent = getGrandparent(curNode);
                        RBNode<T, KeyT>* uncle = getUncle(curNode, gparent);
                        
                        if (uncle && uncle->isRed) {
                            // Parent is red and Uncle is Red
                            // Change both to black and GP to red if not root and continue from GP
                            parent->isRed = false;
                            uncle->isRed = false;
                            if (gparent != root) {
                                gparent->isRed = true;
                            }
                            curNode = gparent;
                            // Continue from GP
                        } else {
                            // Parent is red and Uncle is Black
                            if (curNode == parent->right && parent == gparent->left) {
                                // curNode is right child of parent, parent is left child of gparent
                                
                                leftRotate(parent);

                                curNode = curNode->left;
                                parent = curNode->parent;
                                gparent = getGrandparent(curNode);
                                                    
                            } else if (curNode == parent->left && parent == gparent->right) {
                                // curNode is left child of parent, parent is right child gparent
                                
                                rightRotate(parent);

                                curNode = curNode->right;
                                parent = curNode->parent;
                                gparent = getGrandparent(curNode);
                            }
                            // curNode is left child of parent, parent is left child of gparent
                            parent->isRed = false;
                            gparent->isRed = true;
                            if (curNode == parent->left) {
                                rightRotate(gparent);
                            } else {
                                leftRotate(gparent);
                            }
                            curNode = root;
                        }
                    } else {
                        curNode = root;
                    }
                }
                
            }
            return newRBNode;
        }
        
        void remove(RBNode<T, KeyT>* node) {
            
        }
        
        RBNode<T, KeyT>* find(const KeyT& key) {
            
        }
        
        RBNode<T, KeyT>* getRoot() {
            return root;
        }
        
    private:
        RBNode<T, KeyT>* root;
        
        inline void leftRotate(RBNode<T, KeyT>* node) {
            if (!node->right) {
                return;
            }
            RBNode<T, KeyT>* child = node->right;
            RBNode<T, KeyT>* parent = node->parent;
            if (!parent) {
                root = child;
            } else if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            
            node->right = child->left;
            if (node->right) {
                node->right->parent = node;
            }
            
            child->left = node;
            child->left->parent = child;
        }
        
        inline void rightRotate(RBNode<T, KeyT>* node) {
            if (!node->left) {
                return;
            }
            RBNode<T, KeyT>* child = node->left;
            RBNode<T, KeyT>* parent = node->parent;
            if (!parent) {
                root = child;
            } else if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            
            node->left = child->right;
            if (node->left) {
                node->left->parent = node;  
            }
            
            child->right = node;
            child->right->parent = child;
        }
        
        inline RBNode<T, KeyT>* getGrandparent(RBNode<T, KeyT>* node) {
            if (node && node->parent) {
                return node->parent->parent;
            } else {
                return nullptr;
            }
        }
        
        inline RBNode<T, KeyT>* getUncle(RBNode<T, KeyT>* node, RBNode<T, KeyT>* gp) {
            if (!gp) return nullptr;
            return  (gp->left == node->parent) ? gp->right : gp->left;
        }
};