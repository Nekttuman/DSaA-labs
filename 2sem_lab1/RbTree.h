//
// Created by nektt on 2/6/2023.
//

#ifndef INC_2SEM_LAB1_RBTREE_H
#define INC_2SEM_LAB1_RBTREE_H

#include <iostream>

using namespace std;


template<class T>
class RBTree {
    struct Node {
        T data;
        Node *parent;
        Node *left;
        Node *right;
        int color;
    };

    Node *root;
    Node *TNULL;

    void insertFix(Node *k) {
        Node *u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    lRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        lRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void _print(Node *root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R    ";
                indent += "   ";
            } else {
                cout << "L    ";
                indent += "|  ";
            }

            string sColor = root->color ? "R" : "B";
            cout << root->data << "(" << sColor << ")" << endl;
            _print(root->left, indent, false);
            _print(root->right, indent, true);
        }
    }

public:
    RBTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void lRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rRotate(Node *x) {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    int getHeight(){
        int h = 0;

        return 0;
    }

    void insert(T key) {
        Node *node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        Node *y = nullptr;
        Node *x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    void printTree() {
        if (root) {
            _print(this->root, "", true);
        }
    }
};

#endif //INC_2SEM_LAB1_RBTREE_H
