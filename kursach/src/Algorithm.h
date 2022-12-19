//
// Created by nektt on 12/4/2022.
//

#ifndef MAIN_CPP_ALGORITHM_H
#define MAIN_CPP_ALGORITHM_H

#include "Figures.h"
#include "Svg.h"
#include "Gcode.h"
#include <list>


int doesOverlap(const fig::figVariants &left, const fig::figVariants &right);

class Algorithm {
protected:          // for AlgorithmTest class
    Svg svg;
    Gcode gcode;

    std::vector<std::pair<fig::Point, fig::Point>> m_figSlicePoints;
    std::vector<int> m_figDrawingOrder;

    std::vector<fig::slicedFig> m_slicedFigures;

    void parseSvg(const std::string &path);

    void logSvg();

    int drawParsed(); //SFML

    int drawPath();  //SFML

    void mergeIntersectFigures();

    void setFiguresDrawingOrder();

    void setFiguresSlicePoints();

    void sliceFigures();
    void sliceCircle(const fig::Circle &circle, const fig::Point &startP);
    void sliceSegment(const fig::Segment &seg, const fig::Point &startP, const fig::Point &endP);
    void sliceRect(const fig::Rect &rect, const fig::Point &startP);

public:
    void start(const std::string &svgFilePath, const std::string &gcodeFilePath, int lineWidth_mm) {
        parseSvg(svgFilePath);
        drawParsed();
        std::cout<<svg;
        mergeIntersectFigures();
        setFiguresDrawingOrder();


        for (auto i: m_figDrawingOrder)
            std::cout << i << "  ";
        std::cout<<"\n\n";

        setFiguresSlicePoints();

        for (auto p: m_figSlicePoints)
            std::cout << p.first << " " << p.second << "\n";
        drawPath();

        sliceFigures();

        for (auto f: m_slicedFigures) {
            std::cout << f.ft << " " << f.startP << " " << f.endP << "  { ";
            for (auto p: f.points)
                std::cout<<p<<" ";
            std::cout<<"}\n\n";
        }

        gcode.generateGcode(gcodeFilePath, m_slicedFigures);
    }
};


#endif //MAIN_CPP_ALGORITHM_H