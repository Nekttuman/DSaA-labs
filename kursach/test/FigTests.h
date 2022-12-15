//
// Created by nektt on 12/15/2022.
//

#ifndef MAIN_CPP_FIGTESTS_H
#define MAIN_CPP_FIGTESTS_H

#include <cassert>
#include "../src/Figures.h"
#include <numeric>

using namespace fig;

class FigTests {
    void getDistancePointLineTest() {
        auto eps = std::numeric_limits<double>::epsilon();
        double d = getDistance({{0, 0},
                                {1, 1}}, {1, 0});
        assert(std::abs(d - sqrt(2) / 2) <= eps && "Point doesnt belong line and perpendicular intersects segment");
        assert(getDistance({{0, 1},
                            {1, 1}}, {1, 0}) == 1);
        assert(getDistance({{0,  0},
                            {-1, 0}}, {1, 0}) == 1 && "Point on a line but doesnt belong segment");

        assert(getDistance({{-1, -1},
                            {3,  3}}, {2, 2}) == 0 && "Point on a line");
        d = getDistance({{0, 0},
                         {2, 1}}, {3, 2});
        assert(std::abs(d - sqrt(2)) <= eps &&
               "Point doesnt belong line and perpendicular doesnt intersect segment");

    }

    void getDistanceCircleTest(){
        Circle circle(0,0,2);

        assert(getFiguresDistance(circle, Circle(0,4,1)) == 1);
        assert(getFiguresDistance(circle, Circle(0,3,1)) == 0);
        assert(getFiguresDistance(circle, Circle(0,2,1)) == 0);

        assert(getFiguresDistance(circle, Line({0,3},{1,3})) == 1);
        assert(getFiguresDistance(circle, Line({0,3},{0,4})) == 1);
        assert(getFiguresDistance(circle, Line({0,2},{1,2})) == 0);

        assert(getFiguresDistance(circle, Rect(2,1,-1,4)) == 1);
        assert(getFiguresDistance(circle, Rect(1,1,-1,4)) == 1);
        assert(getFiguresDistance(circle, Rect(2,2,-1,4)) == 0);
        assert(getFiguresDistance(circle, Rect(2,3,-1,4)) == 0);
    }


public:
    void startFigTests() {
        std::cout << "\nFIGURES ALGORITHMS TESTS STARTED\n\n--- point and line getDistance() test ---\n";
        getDistancePointLineTest();

        std::cout << "\n--- Circle and all figures getDistance() test ---\n";
        getDistanceCircleTest();

        std::cout << "\nTESTS PASSED\n";
    }


};


#endif //MAIN_CPP_FIGTESTS_H
