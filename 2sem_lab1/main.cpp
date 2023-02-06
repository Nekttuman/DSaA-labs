#include <iostream>

#include "BSTree.h"
#include "AVLTree.h"
#include "RbTree.h"

#include <chrono>

long long get_working_time(void (*sortFunc)(std::vector<int>::iterator, std::vector<int>::iterator),
                           std::vector<int> data) {
    auto start = std::chrono::high_resolution_clock::now();

    sortFunc(std::begin(data), std::end(data));

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return duration.count();
}

int main() {
    BinarySearchTree<int> bsTree(6);
    bsTree.insert(12);
    bsTree.insert(1);
    bsTree.insert(112);
    bsTree.insert(2);
    bsTree.insert(43);
    bsTree.insert(4);
    bsTree.insert(8);
    bsTree.beautyPrint();

    std::cout<<"\n\n\n";

    AVLTree<int> avlTree(1);
    avlTree.insert(5);
    avlTree.insert(2);
    avlTree.insert(12);
    avlTree.insert(23);
    avlTree.insert(13);
    avlTree.insert(11);
    avlTree.insert(6);

    avlTree.print();

    RBTree<int> rbTree;
    rbTree.insert(2);
    rbTree.insert(12);
    rbTree.insert(1);
    rbTree.insert(11);
    rbTree.insert(11);
    rbTree.insert(123);
    rbTree.insert(1233);
    rbTree.printTree();
    return 0;
}
