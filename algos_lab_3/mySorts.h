//
// Created by delme on 26.10.2022.
//

#ifndef ALGOS_LAB_3_MYSORTS_H
#define ALGOS_LAB_3_MYSORTS_H

#include <iostream>
#include <vector>
#include <random>

namespace mySorts {
    template<class T>
    void insertionSort(T begin, T end) {
        for (auto i = begin + 1; begin != end && i != end; ++i) {
            auto j = i;
            while (*j < *(j - 1)) {
                std::swap(*j, *(j - 1));
                if (j - 1 == begin)
                    break;
                j = (j - 1);
            }
        }
    }

    void insertionSortTest() {
        std::vector<char> v{'1', 'd', 'e', 'f', '4'};
        mySorts::insertionSort(std::begin(v), std::end(v));

        for (auto i: v)
            std::cout << i << " ";

        std::cout << '\n';

        char arr[]{'1', 'd', 'e', 'f', '4'};
        mySorts::insertionSort(std::begin(arr), std::end(arr));

        for (auto i: arr)
            std::cout << i << " ";
    }


    template<class T>
    void selectionSort(T begin, T end) {
        for (T i = begin; begin != end && i != end - 1; ++i)
            for (T j = i + 1; j != end; ++j)
                if (*i > *j)
                    std::swap(*i, *j);
    }

    void selectionSortTest() {
        std::vector<int> v{38, 27, 43, 3, -123, 0, 123};
        mySorts::selectionSort(std::begin(v), std::end(v));

        for (auto i: v)
            std::cout << i << " ";

        std::cout << '\n';

        char arr[]{'1', 'd', 'e', 'f', '4'};
        mySorts::selectionSort(std::begin(arr), std::end(arr));

        for (auto i: arr)
            std::cout << i << " ";
    }

    template<class T>
    void bubbleSort(T begin, T end) {
        for (T i = begin; i != end; ++i)
            for (T j = begin; j != end - 1; ++j) {
                if (*j > *(j + 1))
                    std::swap(*j, *(j + 1));
            }
    }

    void bubbleSortTest() {
        std::vector<int> v{38, 27, 433, -123, 0, 123};
        bubbleSort(std::begin(v), std::end(v));

        for (auto i: v)
            std::cout << i << " ";

        std::cout << '\n';

        char arr[]{'1', 'd', 'e', 'f', '4'};
        bubbleSort(std::begin(arr), std::end(arr));

        for (auto i: arr)
            std::cout << i << " ";
    }


    template<class T>
    void merge(T lbegin, T mid, T end) {
        T rbegin = mid;
        while (lbegin != mid && rbegin != end) {
            if (*lbegin > *rbegin)
                std::swap(*lbegin, *rbegin);
            ++lbegin;
        }
    }

    template<class T>
    void mergeSort(T begin, T end) {
        if (begin == end || begin == end - 1) // empty case
            return;

        T mid = begin + (end - begin) / 2;
        mergeSort(begin, mid);
        mergeSort(mid, end);
        merge(begin, mid, end);
    }

    void mergeSortTest() {
        std::vector<int> v{38, 27, 43, 3};
        mySorts::mergeSort(std::begin(v), std::end(v));

        for (auto i: v)
            std::cout << i << " ";

        std::cout << '\n';

        char arr[]{'1', 'd', 'e', 'f', '4'};
        mySorts::mergeSort(std::begin(arr), std::end(arr));

        for (auto i: arr)
            std::cout << i << " ";
    }

    template<class T>
    void shellSort(T begin, T end) {
        for (auto d = (end - begin) / 2; d != 0; d /= 2)
            for (T i = begin + d; i != end; ++i)
                for (auto j = i; j - begin >= d && *j < *(j - d); j -= d)
                    std::swap(*j, *(j - d));

    }

    void shellSortTest() {
        std::vector<int> v{38, 27, 43, 3};
        mySorts::shellSort(std::begin(v), std::end(v));

        for (auto i: v)
            std::cout << i << " ";

        std::cout << '\n';

        char arr[]{'1', 'd', 'e', 'f', '4'};
        mySorts::shellSort(std::begin(arr), std::end(arr));

        for (auto i: arr)
            std::cout << i << " ";
    }

    template<class T>
    T partition(T begin, T end) {
        T pivot = end - 1;
        T firsthigh = begin;
        for (auto i = begin; i != end - 1; ++i) {
            if (*i < *pivot) {
                std::swap(*firsthigh, *i);
                ++firsthigh;
            }
        }
        std::swap(*pivot, *firsthigh);
        return firsthigh;
    }

    template<class T>
    void quickSort(T begin, T end) {
        if (begin != end) {
            T pivot = partition(begin, end);

            quickSort(begin, pivot);
            quickSort(pivot + 1, end);
        }
    }

    void quickSortTest() {
        std::vector<int> v{38, 27, 43, 3, -123, 0, 123};
        mySorts::quickSort(std::begin(v), std::end(v));

        for (auto i: v)
            std::cout << i << " ";

        std::cout << '\n';

        char arr[]{'1', 'd', 'e', 'f', '4'};
        mySorts::quickSort(std::begin(arr), std::end(arr));

        for (auto i: arr)
            std::cout << i << " ";
    }

}


#endif //ALGOS_LAB_3_MYSORTS_H
