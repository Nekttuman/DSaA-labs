//
// Created by nektt on 12/6/2022.
//

#ifndef MAIN_CPP_SVGPARSETEST_H
#define MAIN_CPP_SVGPARSETEST_H

#include "../src/Svg.h"

#include <cassert>

const std::string prefixPath = "../test/testSvg/";

class SvgParseTest : public Svg {
    void circleParseTest();

    void rectParseTest();

    void fillPolygonParseTest();

    void nonefillPolygonParseTest();

    void fillPolylineParseTest();

    void nonefillPolylineParseTest();

    void lineParseTest();

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
