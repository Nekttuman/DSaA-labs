//
// Created by nektt on 12/4/2022.
//

#ifndef MAIN_CPP_ALGORITHM_H
#define MAIN_CPP_ALGORITHM_H

#include "Figures.h"
#include "Svg.h"
#include "Gcode.h"


int doesOverlap(const fig::figVariants &left, const fig::figVariants &right);

class Algorithm {
protected:          // for AlgorithmTest class
    Svg svg;
    Gcode gcode;

private:
    std::vector<int> figuresDrawingOrder;

public:
    void parseSvg(const std::string &path);

    void logSvg();

    void setGcodeFilePath(const std::string &path);

    void mergeIntersectFigures();

    void setFiguresDrawingOrder();

    void sliceFigures();

    void writeGcodeFile(const std::string& filepath){}
};


#endif //MAIN_CPP_ALGORITHM_H