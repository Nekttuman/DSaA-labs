//
// Created by nektt on 07.02.2023.
//

#ifndef INC_2SEM_LAB1_TIMETESTS_H
#define INC_2SEM_LAB1_TIMETESTS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "BSTree.h"
#include "AVLTree.h"
#include "RbTree.h"

#include <chrono>

std::pair<std::vector<long long>, std::vector<long long>> bstTest() {
    std::fstream in("../test_data/10.txt", std::ios_base::in);

    if (!in.is_open())
        throw;

    std::vector<long long> bstTimes, bstHeights;
    BinarySearchTree<int> bsTree(1);

    auto start = std::chrono::high_resolution_clock::now();
    int data;
    while (in >> data) {
        bsTree.insert(data);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());
    bstHeights.push_back(bsTree.getHeight());

    in.close();
    in.open("../test_data/100.txt", std::ios_base::in);
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree1(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree1.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());
    bstHeights.push_back(bsTree1.getHeight());

    in.close();
    in.open("../test_data/1000.txt");
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree2(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree2.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());
    bstHeights.push_back(bsTree2.getHeight());

    in.close();
    in.open("../test_data/3000.txt");
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree3(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree3.insert(data);
    }
    in.close();
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());

    bstHeights.push_back(bsTree3.getHeight());

    in.close();
    in.open("../test_data/5000.txt");
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree4(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree4.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());

    bstHeights.push_back(bsTree4.getHeight());


    in.close();
    in.open("../test_data/20000.txt");
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree5(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree5.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());

    bstHeights.push_back(bsTree5.getHeight());


    in.close();
    in.open("../test_data/100000.txt");
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree6(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree6.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());

    bstHeights.push_back(bsTree6.getHeight());


    in.close();
    in.open("../test_data/60000.txt");
    if (!in.is_open())
        throw;

    BinarySearchTree<int> bsTree7(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        bsTree7.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    bstTimes.push_back(duration.count());

    bstHeights.push_back(bsTree7.getHeight());

    return {bstTimes, bstHeights};
}


std::pair<std::vector<long long>,std::vector<long long>> rbTest() {
    std::fstream in("../test_data/10.txt", std::ios_base::in);

    if (!in.is_open())
        throw;

    std::vector<long long> rbTimes, rbHeights;
    RBTree<int> rbTree;

    auto start = std::chrono::high_resolution_clock::now();
    int data;
    while (in >> data) {
        rbTree.insert(data);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());
    rbHeights.push_back(rbTree.getHeight());
    in.close();
    in.open("../test_data/100.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree1;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree1.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());
    rbHeights.push_back(rbTree1.getHeight());

    in.close();
    in.open("../test_data/1000.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree2;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree2.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());

    rbHeights.push_back(rbTree2.getHeight());

    in.close();
    in.open("../test_data/3000.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree3;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree3.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());
    rbHeights.push_back(rbTree3.getHeight());

    in.close();
    in.open("../test_data/5000.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree4;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree4.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());
    rbHeights.push_back(rbTree4.getHeight());


    in.close();
    in.open("../test_data/20000.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree5;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree5.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());

    rbHeights.push_back(rbTree5.getHeight());

    in.close();
    in.open("../test_data/100000.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree6;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree6.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());

    rbHeights.push_back(rbTree6.getHeight());

    in.close();
    in.open("../test_data/60000.txt");
    if (!in.is_open())
        throw;

    RBTree<int> rbTree7;

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        rbTree7.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    rbTimes.push_back(duration.count());

    rbHeights.push_back(rbTree7.getHeight());
    return {rbTimes, rbHeights};
}



std::pair<std::vector<long long>,std::vector<long long>> avlTest() {
    std::fstream in("../test_data/10.txt", std::ios_base::in);

    if (!in.is_open())
        throw;

    std::vector<long long> avlTimes, avlHeights;
    AVLTree<int> avlTree(1);

    auto start = std::chrono::high_resolution_clock::now();
    int data;
    while (in >> data) {
        avlTree.insert(data);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());

    in.close();
    in.open("../test_data/100.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree1(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree1.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());

    in.close();
    in.open("../test_data/1000.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree2(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree2.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());

    in.close();
    in.open("../test_data/3000.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree3(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree3.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());

    in.close();
    in.open("../test_data/5000.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree4(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree4.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());


    in.close();
    in.open("../test_data/20000.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree5(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree5.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());


    in.close();
    in.open("../test_data/100000.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree6(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree6.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());


    in.close();
    in.open("../test_data/60000.txt");
    if (!in.is_open())
        throw;

    AVLTree<int> avlTree7(1);

    start = std::chrono::high_resolution_clock::now();
    while (in >> data) {
        avlTree7.insert(data);
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    avlTimes.push_back(duration.count());

    avlHeights.push_back(avlTree.getHeight());
    avlHeights.push_back(avlTree1.getHeight());
    avlHeights.push_back(avlTree2.getHeight());
    avlHeights.push_back(avlTree3.getHeight());
    avlHeights.push_back(avlTree4.getHeight());
    avlHeights.push_back(avlTree5.getHeight());
    avlHeights.push_back(avlTree6.getHeight());
    avlHeights.push_back(avlTree7.getHeight());

    return {avlTimes, avlHeights};
}


#endif //INC_2SEM_LAB1_TIMETESTS_H
