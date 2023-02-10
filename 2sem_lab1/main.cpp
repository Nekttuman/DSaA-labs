#include "timeTests.h"
#include <array>

int main() {
    std::array<std::vector<long long>, 3> bstTimes, avlTimes, rbTimes,
            bstHeights, avlHeights, rbHeights;

    for (int i = 0; i < 3; ++i) {
        bstTimes[i] = bstTest().first;
        rbTimes[i] = rbTest().first;
        avlTimes[i] = avlTest().first;

        bstHeights[i] = bstTest().second;
        rbHeights[i] = rbTest().second;
        avlHeights[i] = avlTest().second;
    }

    for (int i = 0; i < bstTimes[0].size(); ++i) {
        long long bstAverage = (bstTimes[0][i] + bstTimes[1][i] + bstTimes[2][i]) / 3,
                rbAverage = (rbTimes[0][i] + rbTimes[1][i] + rbTimes[2][i]) / 3,
                avlAverage = (avlTimes[0][i] + avlTimes[1][i] + avlTimes[2][i]) / 3;
        std::cout << avlAverage << ", ";// << rbAverage << " " << avlAverage << "\n";
    }


    for (int i = 0; i < bstTimes[0].size(); ++i) {
        long long bstAverage = (bstHeights[0][i] + bstHeights[1][i] + bstHeights[2][i]) / 3,
                rbAverage = (rbHeights[0][i] + rbHeights[1][i] + rbHeights[2][i]) / 3,
                avlAverage = (avlHeights[0][i] + avlHeights[1][i] + avlHeights[2][i]) / 3;
        std::cout << avlAverage << ", " << rbAverage << " " << bstAverage << "\n";
    }

    return 0;
}
