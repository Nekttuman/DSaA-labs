//
// Created by delme on 08.11.2022.
//

#ifndef ALGOS_LAB_4_MYBINARYTREE_H
#define ALGOS_LAB_4_MYBINARYTREE_H

#include <queue>

namespace std {
    string to_string(char c) {
        std::string res;
        res.push_back(c);
        return res;
    }

    string to_string(string s) {
        return s;
    }
}

template<class T>
class BinarySearchTree {
    struct Node {
        Node *parent = nullptr,
                *right = nullptr,
                *left = nullptr;
        T data;
    };

    Node *root = nullptr;

public:
    BinarySearchTree() = default;

    BinarySearchTree(const T &item) {
        root = new Node{nullptr, nullptr, nullptr, item};
    }

    template<class IT>
    BinarySearchTree(IT begin, IT end) {
        root = new Node{nullptr, nullptr, nullptr, *begin};
        ++begin;
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    int insert(T item) {
        auto iter = root;
        auto newNode = new Node{root, nullptr, nullptr, item};

        while (true) {
            if (iter->data > item)
                if (iter->left == nullptr) {
                    iter->left = newNode;
                    newNode->parent = iter;
                    return 0;
                } else
                    iter = iter->left;
            else if (iter->data < item)
                if (iter->right == nullptr) {
                    iter->right = newNode;
                    newNode->parent = iter;
                    return 0;
                } else
                    iter = iter->right;
            else {
                delete newNode;
                return -1;
            }
        }
    }

    void remove(T item) {
        auto iter = root;

        while (true)
            if (iter->data > item)
                if (iter->left == nullptr)
                    return;
                else
                    iter = iter->left;
            else if (iter->data < item)
                if (iter->right == nullptr)
                    return;
                else
                    iter = iter->right;
            else { // contains item in tree

                if (iter->right == nullptr && iter->left == nullptr) {
                    // element to be removed has no children

                    if (iter->parent->right == iter)
                        iter->parent->right = nullptr;
                    else iter->parent->left = nullptr;

                    delete iter;
                    iter = nullptr;
                } else if (iter->right == nullptr) {
                    // element to be removed has only left child

                    if (iter->parent->right == iter)
                        iter->parent->right = iter->left;
                    else
                        iter->parent->left = iter->left;

                    iter->left->parent = iter->parent;

                    delete iter;
                    iter = nullptr;
                } else if (iter->left == nullptr) {
                    // element to be removed has only right child

                    if (iter->parent->right == iter)
                        iter->parent->right = iter->right;
                    else
                        iter->parent->left = iter->right;

                    iter->right->parent = iter->parent;

                    delete iter;
                    iter = nullptr;
                } else {
                    // element to be removed has 2 children

                    Node *succ = findPreSuccessorNode(root, nullptr, item);
                    iter->data = succ->data;

                    if (succ->parent->right == succ)
                        succ->parent->right = nullptr;
                    else succ->parent->left = nullptr;
                    delete succ;

                    succ = nullptr;
                }
                return;
            }

    }

    void bfsPrint() {
        int levelsCount = this->getHeight();
        for (int i = 1; i <= levelsCount; ++i) {
            printLevel(root, i);
            std::cout << "\n";
        }
    }

    T findInorderSuccessor(T item) {
        if (!this->contains(item))
            return item;

        Node *succ = findSuccessorNode(root, nullptr, item);

        return succ->data;
    }

    T findPreorderSuccessor(T item) {
        if (!this->contains(item))
            return item;

        Node *succ = findPreSuccessorNode(root, nullptr, item);

        return succ->data;
    }

    T getMin() {
        auto iter = root;
        while (iter->left != nullptr)
            iter = iter->left;
        return iter->data;
    }

    T getMax() {
        auto iter = root;
        while (iter->right != nullptr)
            iter = iter->right;
        return iter->data;
    }

    bool contains(T item) {
        auto Iter = root;

        while (true) {
            if (Iter->data > item)
                if (Iter->left == nullptr)
                    return false;
                else
                    Iter = Iter->left;
            else if (Iter->data < item)
                if (Iter->right == nullptr)
                    return false;
                else
                    Iter = Iter->right;
            else
                return true;

        }
    }

    void inorderPrint() {
        inorder(root);
        std::cout << "\n";
    }

    void preorderPrint() {
        preorder(root);
        std::cout << "\n";
    }

    void postorderPrint() {
        postorder(root);
        std::cout << "\n";
    }

    int getHeight() const {
        int ans = INT_MIN;
        getLevelCount(root, 0, ans);
        return ans;
    }

    void beautyPrint() {
        int maxWidth = getMaxElemWidth();
        maxWidth = maxWidth % 2 ? maxWidth : maxWidth + 1;
        for (int h = this->getHeight(), ws = 1; h > 0; --h) {

            auto lev = this->getLevel(h);
            std::cout << std::string(ws / 2, ' ');
            for (int i = 0; i < lev.size(); ++i) {
                int curWidth = lev[i].size();
                if (curWidth == 0) {
                    lev[i] = std::string(maxWidth, '*');
                    curWidth = maxWidth;
                }
                int l_ws = (maxWidth - curWidth) / 2;
                int r_ws = curWidth % 2 ? l_ws : l_ws + 1;

                printf("%*s%s%*s", l_ws, "", lev[i].c_str(), r_ws, "");
                std::cout << std::string(ws, ' ');
            }
            std::cout << "\n";
            ws = ws * 2 + 1 + (maxWidth / 2) * 2;
        }
    }

    std::vector<std::string> getLevel(int level) const {
        std::vector<std::string> res;
        getLevelRec(root, res, level);

        return res;
    }

    ~BinarySearchTree() {
        deleteTree(root);
    }


private:
    Node *findSuccessorNode(Node *n, Node *succ, int key) {
        if (n == nullptr)
            return succ;

        if (n->data == key) {
            if (n->right != nullptr)
                return findMinNode(n->right);
        } else if (key < n->data) {
            succ = n;
            return findSuccessorNode(n->left, succ, key);
        } else
            return findSuccessorNode(n->right, succ, key);

        return succ;
    }

    Node *findPreSuccessorNode(Node *n, Node *succ, int key) {
        if (n == nullptr)
            return succ;

        if (n->data == key) {
            if (n->left != nullptr)
                return findMaxNode(n->left);
        } else if (key > n->data) {
            succ = n;
            return findPreSuccessorNode(n->right, succ, key);
        } else
            return findPreSuccessorNode(n->left, succ, key);

        return succ;
    }

    Node *findMinNode(Node *n) {
        while (n->left)
            n = n->left;
        return n;
    }

    Node *findMaxNode(Node *n) {
        while (n->right)
            n = n->right;
        return n;
    }

    void printLevel(Node *n, int level) {
        if (n == nullptr)
            return;
        else if (level == 1)
            std::cout << n->data << " ";
        else if (level > 1) {
            printLevel(n->left, level - 1);
            printLevel(n->right, level - 1);
        }
    }

    void getLevelRec(Node *n, std::vector<std::string> &res, int level) const {
        if (n == nullptr && level == 1) {
            res.push_back("");
            return;
        } else if (n == nullptr) {
            for (int i = 0; i < level; ++i) {
                res.push_back("");
            }
            return;
        } else if (level == 1)
            res.push_back(std::to_string(n->data));
        else if (level > 1) {
            getLevelRec(n->left, res, level - 1);
            getLevelRec(n->right, res, level - 1);
        }
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

    void preorder(Node *n) {
        if (n != nullptr) {
            std::cout << n->data << " ";
            preorder(n->left);
            preorder(n->right);
        }
    }

    void inorder(Node *n) {
        if (n != nullptr) {
            inorder(n->left);

            std::cout << n->data << " ";

            inorder(n->right);
        }
    }

    void postorder(Node *n) {
        if (n != nullptr) {
            postorder(n->right);
            std::cout << n->data << " ";
            postorder(n->left);
        }
    }

    void deleteTree(Node *n) {
        if (n != nullptr) {
            deleteTree(n->right);
            deleteTree(n->left);
            delete n;
            n = nullptr;
        }
    }

    int getMaxElemWidth() {
        int maxWidth = 0;

        for (int h = this->getHeight(); h > 0; --h) {
            auto lev = this->getLevel(h);
            for (const auto &item: lev)
                if (item.size() > maxWidth)
                    maxWidth = item.size();

        }

        return maxWidth;
    }

};


#endif //ALGOS_LAB_4_MYBINARYTREE_H
