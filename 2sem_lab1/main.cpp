#include "timeTests.h"
#include <array>

int main() {
    std::array<std::vector<long long>, 3> bstTimes, avlTimes, rbTimes;

    for (int i = 0; i < 3; ++i) {
        bstTimes[i] = bstTest();
        rbTimes[i] = rbTest();
        avlTimes[i] = avlTest();
    }

    for (int i = 0; i < bstTimes[0].size(); ++i) {
        long long bstAverage = (bstTimes[0][i] + bstTimes[1][i] + bstTimes[2][i]) / 3,
                rbAverage = (rbTimes[0][i] + rbTimes[1][i] + rbTimes[2][i]) / 3,
                avlAverage = (avlTimes[0][i] + avlTimes[1][i] + avlTimes[2][i]) / 3;
        std::cout << rbAverage << ", ";// << rbAverage << " " << avlAverage << "\n";
    }

    return 0;
}
