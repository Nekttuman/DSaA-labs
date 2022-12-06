//
// Created by nektt on 12/6/2022.
//

#ifndef MAIN_CPP_ALGORITHMTESTS_H
#define MAIN_CPP_ALGORITHMTESTS_H

#include "../src/Algorithm.h"
#include <cassert>

class AlgorithmTests : public Algorithm {
    void testCircleOverlap() {
        parseSvg("../test/testSvg/CircleOverlap1.svg");
        if (svg.getFiguresCount() != 2) throw std::runtime_error("CircleOverlap1.svg parse error");
        fig::Circle c1 = std::get<fig::Circle>(*svg.begin()),
                c2 = std::get<fig::Circle>(*(svg.begin() + 1));

        assert(isOverlap(c1, c2) &&
               "First overlaps second. test file: CircleOverlap1.svg");
        std::cout << "First overlaps second: PASSED\n";

        parseSvg("../test/testSvg/CircleOverlap2.svg");
        if (svg.getFiguresCount() != 2) throw std::runtime_error("CircleOverlap2.svg parse error");
        c1 = std::get<fig::Circle>(*svg.begin());
        c2 = std::get<fig::Circle>(*(svg.begin() + 1));
        assert(isOverlap(c2, c1) &&
               "Second overlaps first. test file: CircleOverlap2.svg");
        std::cout << "Second overlaps first: PASSED\n";

        parseSvg("../test/testSvg/CircleDontOverlap.svg");
        if (svg.getFiguresCount() != 2) throw std::runtime_error("CircleDontOverlap.svg parse error");
        c1 = std::get<fig::Circle>(*svg.begin());
        c2 = std::get<fig::Circle>(*(svg.begin() + 1));
        assert(!isOverlap(c2, c1) &&
               "Circles not overlaps. test file: CircleDontOverlap.svg");
        std::cout << "Circles not overlaps: PASSED\n";
    }


public:

    void startTests() {
        std::cout << "\nTESTS STARTED\n\n--- Circle overlap test ---\n";
        testCircleOverlap();


        std::cout << "\n\nTESTS PASSED\n";
    }
};


#endif //MAIN_CPP_ALGORITHMTESTS_H
