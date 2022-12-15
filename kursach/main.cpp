#include "src/Algorithm.h"

#include "test/AlgorithmTests.h"
#include "test/SvgParseTest.h"
#include "test/FigTests.h"

int main() {
    Algorithm alg;
//    alg.parseSvg("../test.svg");
//    alg.drawParsed();
//    alg.logSvg();
//    alg.setGcodeFilePath("../test.gcode");
//
//    alg.mergeIntersectFigures();
//    alg.logSvg();
//
//    alg.sliceFigures();
//    alg.generateGcode();

FigTests fTest;
fTest.startFigTests();

//    SvgParseTest spTest;
//    spTest.startTests();
//
//    AlgorithmTests algTest;
//    algTest.startTests();
    return 0;
}