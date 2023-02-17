//
// Created by nektt on 2/6/2023.
//

#ifndef INC_2SEM_LAB1_AVLTREE_H
#define INC_2SEM_LAB1_AVLTREE_H

#include <iostream>

template<class T>
class AVLTree {
    struct Node {
        T data;
        int h;
        int balanceFactor;
        Node *parent = nullptr, *right = nullptr, *left = nullptr;
    };

    void _printTree(Node *root) {
        if(root != NULL)
        {
            std::cout << root->data << " ";
            _printTree(root->left);
            _printTree(root->right);
        }
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        if (y->left == nullptr)
            y->h = y->right->h +1;
        else
            y->h = std::max(y->left->h, y->right->h) + 1;
        if (x->left == nullptr)
            x->h = x->right->h +1;
        else
        x->h = std::max(x->left->h, x->right->h) + 1;
        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        if (x->right == nullptr)
            x->h = x->left->h+1;
        else
        x->h = std::max(x->left->h, x->right->h) + 1;
        if (y->right == nullptr)
            y->h = y->left->h+1;
        else
            y->h = std::max(y->left->h, y->right->h) + 1;
        return y;
    }

    int calcBalanceFactor(Node *N) {
        if (N == NULL || N->right == nullptr && N->left == nullptr)
            return 0;
        if (N->right == nullptr)
            return N->left->h;
        if (N->left == nullptr)
            return 0 - N->right->h;
        return (N->left->h - N->right->h);
    }

    Node *newNode(int data) {
        Node *node = new Node();
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        node->h = 1;
        return (node);
    }

    Node *insertNode(Node *node, T newData) {
        if (node == nullptr)
            return new Node{newData, 0, 0, nullptr, nullptr, nullptr};
        if (newData < node->data)
            node->left = insertNode(node->left, newData);
        else if (newData > node->data)
            node->right = insertNode(node->right, newData);
        else // Equal keys are not allowed in BST
            return node;

        /* 2. Update height of this ancestor node */
        node->h =
                1 + std::max(node->left == nullptr ? 0 : node->left->h,
                             node->right == nullptr ? 0 : node->right->h);

        int balance = calcBalanceFactor(node);

        if (balance > 1 && newData < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && newData > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && newData > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && newData < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void getLevelCount(Node *n, int count, int &max_count) const {
        if (n == nullptr)
            max_count = (max_count > count) ? max_count : count;
        else {
            count++;
            getLevelCount(n->left, count, max_count);
            getLevelCount(n->right, count, max_count);
        }
    }

public:
    Node *root;

    AVLTree(T rootData) {
        root = new Node{rootData, 1, 0, nullptr, nullptr, nullptr};
    }

    void print() {
        _printTree(root);
    }

    int insert(T newData) {
        auto iter = root;

        while (true) {
            if (iter->data > newData)
                if (iter->left == nullptr) {
                    insertNode(iter, newData);
                    return 0;
                } else
                    iter = iter->left;
            else if (iter->data < newData)
                if (iter->right == nullptr) {
                    insertNode(iter, newData);
                    return 0;
                } else
                    iter = iter->right;
            else {
                return -1;
            }
        }
    }

    int getHeight() const {
        int ans = INT_MIN;
        getLevelCount(root, 0, ans);
        return ans;
    }
};


#endif //INC_2SEM_LAB1_AVLTREE_H
