//
// Created by nektt on 12/6/2022.
//

#ifndef MAIN_CPP_SVGPARSETEST_H
#define MAIN_CPP_SVGPARSETEST_H

#include "../src/Svg.h"

#include <cassert>

const std::string prefixPath = "../test/testSvg/";

class SvgParseTest : public Svg {
    void circleParseTest() {
        parse(prefixPath + "Circle.svg");
        fig::Circle circle = std::get<fig::Circle>(m_figures[0]);
        assert(circle == fig::Circle(150, 100, 80) &&
               "Circle parse. test file: Circle.svg");
        std::cout << "Circle parse: PASSED\n";
        empty();
    }

    void rectParseTest() {
        parse(prefixPath + "Rect.svg");
        fig::Rect rect = std::get<fig::Rect>(m_figures[0]);
        assert(rect == fig::Rect(200,50,100,40) &&
               "Rect parse. test file: Rect.svg");
        std::cout << "Rect parse: PASSED\n";
        empty();
    }

    void fillPolygonParseTest() {
        parse(prefixPath + "fillPolygon.svg");
        fig::Polygon poly = std::get<fig::Polygon>(m_figures[0]);
        fig::Polygon trgt({{0, 100}, {50, 25}, {50, 75}, {100, 0}});
        assert(poly == trgt &&
               "filled polygon parse. test file: fillPolygon.svg");
        std::cout << "filled polygon parse: PASSED\n";
        empty();
    }

    void nonefillPolygonParseTest() {
        parse(prefixPath + "nonefillPolygon.svg");
        fig::Path poly = std::get<fig::Path>(m_figures[0]);
        fig::Path trgt({{0, 100}, {50, 25}, {50, 75}, {100, 0}, {0,100}});
        assert(poly == trgt &&
               "none filled polygon parse. test file: nonefillPolygon.svg");
        std::cout << "none filled polygon parse: PASSED\n";
        empty();
    }

    void fillPolylineParseTest() {
        parse(prefixPath + "fillPolyline.svg");
        fig::Polygon poly = std::get<fig::Polygon>(m_figures[0]);
        fig::Polygon trgt({{0, 100}, {50, 25}, {50, 75}, {100, 0}});
        assert(poly == trgt &&
               "filled polyline parse. test file: fillPolyline.svg");
        std::cout << "filled polyline parse: PASSED\n";
        empty();
    }

    void nonefillPolylineParseTest() {
        parse(prefixPath + "nonefillPolyline.svg");
        fig::Path poly = std::get<fig::Path>(m_figures[0]);
        fig::Path trgt({{0, 100}, {50, 25}, {50, 75}, {100, 0}, {0,100}});
        assert(poly == trgt &&
               "none filled polyline parse. test file: nonefillPolyline.svg");
        std::cout << "none filled polyline parse: PASSED\n";
        empty();
    }

    void lineParseTest() {
        parse(prefixPath + "Line.svg");
        fig::Line poly = std::get<fig::Line>(m_figures[0]);
        assert(poly == fig::Line(0,80,100,20) &&
               "line parse. test file: Line.svg");
        std::cout << "line parse: PASSED\n";
        empty();
    }

public:

    void startTests() {
        std::cout << "\nSVG PARSE CLASS TESTS STARTED\n\n";

        circleParseTest();
        rectParseTest();
        fillPolygonParseTest();
        nonefillPolygonParseTest();
        fillPolylineParseTest();
        nonefillPolylineParseTest();
        lineParseTest();


        std::cout << "\nTESTS PASSED\n";
    }
};


#endif //MAIN_CPP_SVGPARSETEST_H
