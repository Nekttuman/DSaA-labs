#include "timeTests.h"
#include <array>

int main() {
    std::array<std::vector<long long>, 100> bstTimes, avlTimes, rbTimes,
            bstHeights, avlHeights, rbHeights;

    for (int i = 0; i < 100; ++i) {
        std::cout << i << '\n';
        bstTimes[i] = bstTest().first;
        rbTimes[i] = rbTest().first;
        avlTimes[i] = avlTest().first;

        bstHeights[i] = bstTest().second;
        rbHeights[i] = rbTest().second;
        avlHeights[i] = avlTest().second;
    }


    std::vector<long long> bstAverages, rbAverages, avlAverages;
    for (int i = 0; i < bstTimes[0].size(); ++i) {
        long long bstAverage = 0;
        long long rbAverage = 0;
        long long avlAverage = 0;
        for (int j = 0; j < bstTimes.size(); ++j) {

            rbAverage += rbTimes[j][i];
            avlAverage += avlTimes[j][i];
            bstAverage += bstTimes[j][i];
        }
        rbAverages.push_back(rbAverage / bstTimes.size());
        avlAverages.push_back(avlAverage / bstTimes.size());
        bstAverages.push_back(bstAverage / bstTimes.size());
    }

    for (auto i: rbAverages)
        std::cout << i << ", ";
    std::cout << '\n';
    for (auto i: bstAverages)
        std::cout << i << ", ";
    std::cout << '\n';
    for (auto i: avlAverages)
        std::cout << i << ", ";
    std::cout << '\n';

    rbAverages.clear();
    avlAverages.clear();
    bstAverages.clear();
    std::cout << "Heights:\navl rb bst\n";
    for (int i = 0; i < bstHeights[0].size(); ++i) {
        long long bstAverage = 0;
        long long rbAverage = 0;
        long long avlAverage = 0;
        for (int j = 0; j < bstHeights.size(); ++j) {

            rbAverage += rbHeights[j][i];
            avlAverage += avlHeights[j][i];
            bstAverage += bstHeights[j][i];
        }
        rbAverages.push_back(rbAverage / bstTimes.size());
        avlAverages.push_back(avlAverage / bstTimes.size());
        bstAverages.push_back(bstAverage / bstTimes.size());
//        std::cout << avlAverage/bstHeights.size() << ", " << rbAverage/bstHeights.size() << " " << bstAverage/bstHeights.size() << "\n";
    }
    for (auto i: rbAverages)
        std::cout << i << ", ";
    std::cout << '\n';
    for (auto i: bstAverages)
        std::cout << i << ", ";
    std::cout << '\n';
    for (auto i: avlAverages)
        std::cout << i << ", ";
    std::cout << '\n';

    return 0;
}
