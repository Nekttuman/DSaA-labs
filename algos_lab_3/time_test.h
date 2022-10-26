//
// Created by delme on 26.10.2022.
//

#ifndef ALGOS_LAB_3_TIME_TEST_H
#define ALGOS_LAB_3_TIME_TEST_H

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <thread>
#include <algorithm>


enum sortType {
    bubble,
    shell,
    quick,
    insertion,
    selection,
    merge,
    std_sort
};


void write_working_time_to_file(sortType st, std::fstream &file, std::vector<int> random_data,
                                std::vector<int> ascending_sorted_data, std::vector<int> descending_sorted_data);

void algorithms_time_test();

#endif //ALGOS_LAB_3_TIME_TEST_H
