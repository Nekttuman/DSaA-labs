//
// Created by nektt on 3/26/2023.
//

#ifndef LAB_ALGO_H
#define LAB_ALGO_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <sstream>
#include <queue>

using namespace std;

namespace Algo {
    // 1.
    string HA_Compress(const string &text);

    // 2.
    string RLE_Compress(const string &input);

    // 3.
    string LZ78_Compress(const string &input);

    // 4.
    string BWT_Compress(const string &input);

    // 5.
    string MTF_Compress(const string &input_str);

    // 6.
    string AC_Compress(const string &text);

    // 7.
    string ppm_encode(const string &input);
}


#endif //LAB_ALGO_H
