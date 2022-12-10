//
// Created by nektt on 12/10/2022.
//

#include "AlgorithmTests.h"

void AlgorithmTests::testCircleOverlapsCircle() {
    parseSvg("../test/testSvg/CircleOverlap1.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlap1.svg parse error");
    fig::Circle c1 = std::get<fig::Circle>(*svg.begin()),
            c2 = std::get<fig::Circle>(*(svg.begin() + 1));
    assert(isOverlap(c1, c2) &&
           "First overlaps second. test file: CircleOverlap1.svg");
    std::cout << "First overlaps second: PASSED\n";

    parseSvg("../test/testSvg/CircleOverlap2.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlap2.svg parse error");
    c1 = std::get<fig::Circle>(*svg.begin());
    c2 = std::get<fig::Circle>(*(svg.begin() + 1));
    assert(isOverlap(c2, c1) &&
           "Second overlaps first. test file: CircleOverlap2.svg");
    std::cout << "Second overlaps first: PASSED\n";

    parseSvg("../test/testSvg/CircleDontOverlap.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleDontOverlap.svg parse error");
    c1 = std::get<fig::Circle>(*svg.begin());
    c2 = std::get<fig::Circle>(*(svg.begin() + 1));
    assert(!isOverlap(c2, c1) &&
           "Circles not overlaps. test file: CircleDontOverlap.svg");
    std::cout << "Circles not overlaps: PASSED\n";
}


void AlgorithmTests::testCircleOverlapsLine() {
    parseSvg("../test/testSvg/CircleOverlapLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlapLine.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*svg.begin());
    fig::Line line = std::get<fig::Line>(*(svg.begin() + 1));
    assert(isOverlap(circle, line) &&
           "Circle overlaps line. test file: CircleOverlapLine.svg");
    std::cout << "Circle overlaps line: PASSED\n";

    parseSvg("../test/testSvg/CircleIntersectLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectLine.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    line = std::get<fig::Line>(*(svg.begin() + 1));
    assert(!isOverlap(circle, line) &&
           "Circle intersect line. test for overlap return false. test file: CircleIntersectLine.svg");
    std::cout << "Circle intersect line: PASSED\n";

    parseSvg("../test/testSvg/CircleNotIntersectLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleNotIntersectLine.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    line = std::get<fig::Line>(*(svg.begin() + 1));
    assert(!isOverlap(circle, line) &&
           "Circle not intersect line. test for overlap return false. test file: CircleNotIntersectLine.svg");
    std::cout << "Circle not intersect line: PASSED\n";
}

void AlgorithmTests::testCircleOverlapsRect() {
    parseSvg("../test/testSvg/CircleOverlapRect.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlapRect.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*svg.begin());
    fig::Rect rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(isOverlap(circle, rect) &&
           "Circle overlaps rect. test file: CircleOverlapRect.svg");
    std::cout << "Circle overlaps rect: PASSED\n";


    parseSvg(prefixPath + "CircleIntersectRect1.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect1.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!isOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect1.svg");
    std::cout << "Circle don't overlaps rect 1/4: PASSED\n";

    parseSvg(prefixPath + "CircleIntersectRect2.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect2.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!isOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect2.svg");
    std::cout << "Circle don't overlaps rect 2/4: PASSED\n";

    parseSvg(prefixPath + "CircleIntersectRect3.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect3.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!isOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect3.svg");
    std::cout << "Circle don't overlaps rect 3/4: PASSED\n";

    parseSvg(prefixPath + "CircleIntersectRect4.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect4.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!isOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect4.svg");
    std::cout << "Circle don't overlaps rect 4/4: PASSED\n";
}

void AlgorithmTests::testCircleOverlapsPath(){

}