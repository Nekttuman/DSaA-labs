//
// Created by nektt on 12/6/2022.
//

#ifndef MAIN_CPP_ALGORITHMTESTS_H
#define MAIN_CPP_ALGORITHMTESTS_H

#include "../src/Algorithm.h"
#include <cassert>



class AlgorithmTests : public Algorithm {
    const std::string prefixPath = "../test/testSvg/";

    void testCircleOverlapsCircle();
    void testCircleOverlapsLine();
    void testCircleOverlapsRect();
    void testCircleOverlapsPath();
    void testCircleOverlapsPolygon();

    void testRectOverlapsCircle();
    void testRectOverlapsLine();
    void testRectOverlapsRect();
    void testRectOverlapsPath();
    void testRectOverlapsPolygon();

public:

    void startTests() {
        std::cout << "\nALGORITHMS TESTS STARTED\n\n--- Circle overlaps circle test ---\n";
        testCircleOverlapsCircle();

        std::cout << "\n\n--- Circle overlaps line test ---\n";
        testCircleOverlapsLine();

        std::cout << "\n\n--- Circle overlaps rect test ---\n";
        testCircleOverlapsRect();

        std::cout << "\n\n--- Circle overlaps path test ---\n";
        testCircleOverlapsPath();

        std::cout << "\n\n--- Circle overlaps polygon test ---\n";
        testCircleOverlapsPolygon();

        std::cout << "\nTESTS PASSED\n";


        std::cout << "\n\n--- Rect overlaps circle test ---\n";
        testRectOverlapsCircle();

        std::cout << "\n\n--- Rect overlaps line test ---\n";
        testRectOverlapsLine();

        std::cout << "\n\n--- Rect overlaps rect test ---\n";
        testRectOverlapsRect();

        std::cout << "\n\n--- Rect overlaps path test ---\n";
        testRectOverlapsPath();

        std::cout << "\n\n--- Rect overlaps polygon test ---\n";
        testRectOverlapsPolygon();

        std::cout << "\nTESTS PASSED\n";
    }
};


#endif //MAIN_CPP_ALGORITHMTESTS_H
