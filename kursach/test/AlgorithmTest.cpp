//
// Created by nektt on 12/10/2022.
//

#include "AlgorithmTests.h"

void AlgorithmTests::testCircleOverlapsCircle() {
    parseSvg(prefixPath + "Circles/CircleOverlap1.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlap1.svg parse error");
    fig::Circle c1 = std::get<fig::Circle>(*svg.begin()),
            c2 = std::get<fig::Circle>(*(svg.begin() + 1));
    assert(doesOverlap(c1, c2) &&
           "First overlaps second. test file: CircleOverlap1.svg");
    std::cout << "First overlaps second: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleOverlap2.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlap2.svg parse error");
    c1 = std::get<fig::Circle>(*svg.begin());
    c2 = std::get<fig::Circle>(*(svg.begin() + 1));
    assert(doesOverlap(c2, c1) &&
           "Second overlaps first. test file: CircleOverlap2.svg");
    std::cout << "Second overlaps first: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleDontOverlap.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleDontOverlap.svg parse error");
    c1 = std::get<fig::Circle>(*svg.begin());
    c2 = std::get<fig::Circle>(*(svg.begin() + 1));
    assert(!doesOverlap(c2, c1) &&
           "Circles not overlaps. test file: CircleDontOverlap.svg");
    std::cout << "Circles not overlaps: PASSED\n";
}


void AlgorithmTests::testCircleOverlapsLine() {
    parseSvg(prefixPath + "Circles/CircleOverlapLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlapLine.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*svg.begin());
    fig::Line line = std::get<fig::Line>(*(svg.begin() + 1));
    assert(doesOverlap(circle, line) &&
           "Circle overlaps line. test file: CircleOverlapLine.svg");
    std::cout << "Circle overlaps line: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleIntersectLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectLine.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    line = std::get<fig::Line>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, line) &&
           "Circle intersect line. test for overlap return false. test file: CircleIntersectLine.svg");
    std::cout << "Circle intersect line: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleNotIntersectLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleNotIntersectLine.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    line = std::get<fig::Line>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, line) &&
           "Circle not intersect line. test for overlap return false. test file: CircleNotIntersectLine.svg");
    std::cout << "Circle not intersect line: PASSED\n";
}

void AlgorithmTests::testCircleOverlapsRect() {
    parseSvg(prefixPath + "Circles/CircleOverlapRect.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlapRect.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*svg.begin());
    fig::Rect rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(doesOverlap(circle, rect) &&
           "Circle overlaps rect. test file: CircleOverlapRect.svg");
    std::cout << "Circle overlaps rect: PASSED\n";


    parseSvg(prefixPath + "Circles/CircleIntersectRect1.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect1.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect1.svg");
    std::cout << "Circle don't overlaps rect 1/4: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleIntersectRect2.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect2.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect2.svg");
    std::cout << "Circle don't overlaps rect 2/4: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleIntersectRect3.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect3.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect3.svg");
    std::cout << "Circle don't overlaps rect 3/4: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleIntersectRect4.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectRect4.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, rect) &&
           "Circle don't overlaps rect. test file: CircleIntersectRect4.svg");
    std::cout << "Circle don't overlaps rect 4/4: PASSED\n";
}

void AlgorithmTests::testCircleOverlapsPath(){
    parseSvg(prefixPath + "Circles/CircleOverlapsPath.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlapsPath.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*svg.begin());
    fig::Path path = std::get<fig::Path>(*(svg.begin() + 1));
    assert(doesOverlap(circle, path) &&
           "Circle overlaps path. test file: CircleOverlapsPath.svg");
    std::cout << "Circle overlaps path (polyline): PASSED\n";

    parseSvg(prefixPath + "Circles/CircleIntersectPath.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectPath.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    path = std::get<fig::Path>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, path) &&
           "Circle dont overlaps path. test file: CircleOverlapsPath.svg");
    std::cout << "Circle dont overlaps path (polyline) 1/2: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleNotIntersectPath.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleNotIntersectPath.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    path = std::get<fig::Path>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, path) &&
           "Circle dont overlaps path. test file: CircleOverlapsPath.svg");
    std::cout << "Circle dont overlaps path (polyline) 2/2: PASSED\n";
}


void AlgorithmTests::testCircleOverlapsPolygon(){
    parseSvg(prefixPath + "Circles/CircleOverlapsPolygon.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleOverlapsPolygon.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*svg.begin());
    fig::Polygon polygon = std::get<fig::Polygon>(*(svg.begin() + 1));
    assert(doesOverlap(circle, polygon) &&
           "Circle overlaps polygon. test file: CircleOverlapsPath.svg");
    std::cout << "Circle overlaps polygon: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleIntersectPolygon.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleIntersectPolygon.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    polygon = std::get<fig::Polygon>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, polygon) &&
           "Circle dont overlaps polygon. test file: CircleOverlapsPolygon.svg");
    std::cout << "Circle dont overlaps polygon 1/2: PASSED\n";

    parseSvg(prefixPath + "Circles/CircleNotIntersectPolygon.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("CircleNotIntersectPolygon.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    polygon = std::get<fig::Polygon>(*(svg.begin() + 1));
    assert(!doesOverlap(circle, polygon) &&
           "Circle dont overlaps polygon. test file: CircleOverlapsPolygon.svg");
    std::cout << "Circle dont overlaps polygon 2/2: PASSED\n";
}



/////////////////////////// RECT///////////////////////////////


void AlgorithmTests::testRectOverlapsCircle() {
    parseSvg(prefixPath + "Rects/RectOverlapsCircle.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectOverlapsCircle.svg parse error");
    fig::Circle circle = std::get<fig::Circle>(*(svg.begin()+1));
    fig::Rect rect = std::get<fig::Rect>(*svg.begin());
    assert(doesOverlap(rect, circle) &&
           "Rect overlaps circle. test file: RectOverlapsCircle.svg");
    std::cout << "Rect overlaps circle: PASSED\n";

    parseSvg(prefixPath + "Rects/RectIntersectsCircle.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectIntersectsCircle.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(rect, circle) &&
           "Rect dont overlaps circle. test file: RectIntersectsCircle.svg");
    std::cout << "Rect dont overlaps circle (1/2): PASSED\n";

    parseSvg(prefixPath + "Rects/RectDontIntersectCircle.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectDontIntersectsCircle.svg parse error");
    circle = std::get<fig::Circle>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(rect, circle) &&
           "Rect dont overlaps circle. test file: RectDontIntersectsCircle.svg");
    std::cout << "Rect dont overlaps circle (2/2): PASSED\n";
}


void AlgorithmTests::testRectOverlapsLine() {
    parseSvg(prefixPath + "Rects/RectOverlapsLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectOverlapsLine.svg parse error");
    fig::Line line = std::get<fig::Line>(*svg.begin());
    fig::Rect rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(doesOverlap(rect, line) &&
           "Rect overlaps circle. test file: RectOverlapsLine.svg");
    std::cout << "Rect overlaps line: PASSED\n";

    parseSvg(prefixPath + "Rects/RectIntersectsLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectIntersectsLine.svg parse error");
    line = std::get<fig::Line>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(rect, line) &&
           "Rect dont overlaps line. test file: RectIntersectsLine.svg");
    std::cout << "Rect dont overlaps line (1/2): PASSED\n";

    parseSvg(prefixPath + "Rects/RectDontIntersectLine.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectDontIntersectsLine.svg parse error");
    line = std::get<fig::Line>(*svg.begin());
    rect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(rect, line) &&
           "Rect dont overlaps line. test file: RectDontIntersectsLine.svg");
    std::cout << "Rect dont overlaps line (2/2): PASSED\n";
}

void AlgorithmTests::testRectOverlapsRect() {
    parseSvg(prefixPath + "Rects/RectOverlapsRect.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectOverlapsRect.svg parse error");
    fig::Rect lRect = std::get<fig::Rect>(*svg.begin());
    fig::Rect rRect = std::get<fig::Rect>(*(svg.begin()+1));
    assert(doesOverlap(lRect, rRect) &&
           "Rect overlaps rect. test file: RectOverlapsRect.svg");
    std::cout << "Rect overlaps rect: PASSED\n";

    parseSvg(prefixPath + "Rects/RectIntersectsRect.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectIntersectsRect.svg parse error");
    lRect = std::get<fig::Rect>(*svg.begin());
    rRect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(lRect, rRect) &&
           "Rect dont overlaps rect. test file: RectIntersectsRect.svg");
    std::cout << "Rect dont overlaps rect (1/2): PASSED\n";

    parseSvg(prefixPath + "Rects/RectDontIntersectRect.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectDontIntersectsRect.svg parse error");
    lRect = std::get<fig::Rect>(*svg.begin());
    rRect = std::get<fig::Rect>(*(svg.begin() + 1));
    assert(!doesOverlap(lRect, rRect) &&
           "Rect dont overlaps rect. test file: RectDontIntersectsRect.svg");
    std::cout << "Rect dont overlaps rect (2/2): PASSED\n";
}

void AlgorithmTests::testRectOverlapsPath(){
    parseSvg(prefixPath + "Rects/RectOverlapsPath.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectOverlapsPath.svg parse error");
    fig::Rect lRect = std::get<fig::Rect>(*svg.begin());
    fig::Path path = std::get<fig::Path>(*(svg.begin() + 1));
    assert(doesOverlap(lRect, path) &&
           "Rect overlaps path. test file: RectOverlapsPath.svg");
    std::cout << "Rect overlaps path: PASSED\n";

    parseSvg(prefixPath + "Rects/RectIntersectsPath.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectIntersectsPath.svg parse error");
    lRect = std::get<fig::Rect>(*svg.begin());
    path = std::get<fig::Path>(*(svg.begin() + 1));
    assert(!doesOverlap(lRect, path) &&
           "Rect dont overlaps path. test file: RectIntersectsPath.svg");
    std::cout << "Rect dont overlaps path (1/2): PASSED\n";

    parseSvg(prefixPath + "Rects/RectDontIntersectPath.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectDontIntersectsPath.svg parse error");
    lRect = std::get<fig::Rect>(*svg.begin());
    path = std::get<fig::Path>(*(svg.begin() + 1));
    assert(!doesOverlap(lRect, path) &&
           "Rect dont overlaps path. test file: RectDontIntersectsPath.svg");
    std::cout << "Rect dont overlaps path (2/2): PASSED\n";
}


void AlgorithmTests::testRectOverlapsPolygon(){ //TODO
    parseSvg(prefixPath + "Rects/RectOverlapsPolygon.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectOverlapsPolygon.svg parse error");
    fig::Rect lRect = std::get<fig::Rect>(*svg.begin());
    fig::Polygon polygon = std::get<fig::Polygon>(*(svg.begin() + 1));
    assert(doesOverlap(lRect, polygon) &&
           "Rect overlaps polygon. test file: RectOverlapsPolygon.svg");
    std::cout << "Rect overlaps polygon: PASSED\n";

    parseSvg(prefixPath + "Rects/RectIntersectsPolygon.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectIntersectsPolygon.svg parse error");
    lRect = std::get<fig::Rect>(*svg.begin());
    polygon = std::get<fig::Polygon>(*(svg.begin() + 1));
    assert(!doesOverlap(lRect, polygon) &&
           "Rect dont overlaps polygon. test file: RectIntersectsPolygon.svg");
    std::cout << "Rect dont overlaps polygon (1/2): PASSED\n";

    parseSvg(prefixPath + "Rects/RectDontIntersectPolygon.svg");
    if (svg.getFiguresCount() != 2)
        throw std::runtime_error("Rects/RectDontIntersectsPolygon.svg parse error");
    lRect = std::get<fig::Rect>(*svg.begin());
    polygon = std::get<fig::Polygon>(*(svg.begin() + 1));
    assert(!doesOverlap(lRect, polygon) &&
           "Rect dont overlaps polygon. test file: RectDontIntersectsPolygon.svg");
    std::cout << "Rect dont overlaps polygon (2/2): PASSED\n";

}