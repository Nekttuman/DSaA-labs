//
// Created by nektt on 12/6/2022.
//

#ifndef MAIN_CPP_ALGORITHMTESTS_H
#define MAIN_CPP_ALGORITHMTESTS_H

#include "../src/Algorithm.h"
#include <cassert>



class AlgorithmTests : public Algorithm {
    const std::string prefixPath = "../test/testSvg/";

    void сircleOverlapsCircleTest();
    void circleOverlapsLineTest();
    void circleOverlapsRectTest();
    void circleOverlapsPathTest();
    void circleOverlapsPolygonTest();

    void rectOverlapsCircleTest();
    void testRectOverlapsLine();
    void testRectOverlapsRect();
    void testRectOverlapsPath();
    void testRectOverlapsPolygon();

    void setFiguresDrawingOrderTest();

public:

    void startTests() {
        std::cout << "\nALGORITHMS TESTS STARTED\n\n--- Circle overlaps circle test ---\n";
        сircleOverlapsCircleTest();

        std::cout << "\n\n--- Circle overlaps line test ---\n";
        circleOverlapsLineTest();

        std::cout << "\n\n--- Circle overlaps rect test ---\n";
        circleOverlapsRectTest();

        std::cout << "\n\n--- Circle overlaps path test ---\n";
        circleOverlapsPathTest();

        std::cout << "\n\n--- Circle overlaps polygon test ---\n";
        circleOverlapsPolygonTest();


        std::cout << "\n\n--- Rect overlaps circle test ---\n";
        rectOverlapsCircleTest();

        std::cout << "\n\n--- Rect overlaps line test ---\n";
        testRectOverlapsLine();

        std::cout << "\n\n--- Rect overlaps rect test ---\n";
        testRectOverlapsRect();

        std::cout << "\n\n--- Rect overlaps path test ---\n";
        testRectOverlapsPath();

        std::cout << "\n\n--- Rect overlaps polygon test ---\n";
        testRectOverlapsPolygon();



        std::cout << "\n\n--- setFiguresDrawingOrder test ---\n";
        setFiguresDrawingOrderTest();

        std::cout << "\nTESTS PASSED\n";
    }
};


#endif //MAIN_CPP_ALGORITHMTESTS_H
