//
// Created by nektt on 12/4/2022.
//

#include "Algorithm.h"


//////////////////////////////////////// FUNCTIONS ////////////////////////////////////////////////

int isOverlap(const fig::figVariants &left, const fig::figVariants &right) {
    // return 0 if figs don't overlap
    //        1 if f1 overlaps f2
    //        2 if f2 overlaps f1
    //
    switch (left.index()) {
        case fig::CIRCLE:
            return doesOverlap(std::get<fig::Circle>(left), right);
        case fig::LINE:
            return doesOverlap(std::get<fig::Line>(left), right);
        case fig::RECT:
            return doesOverlap(std::get<fig::Rect>(left), right);
        case fig::POLYGON:
            return doesOverlap(std::get<fig::Polygon>(left), right);
        case fig::PATH:
            return doesOverlap(std::get<fig::Path>(left), right);
    }
    return 0;
}


//////////////////////////////////////// METHODS ////////////////////////////////////////////////


void Algorithm::parseSvg(const std::string &path) {
    svg.empty();
    svg.parse(path);
}

void Algorithm::logSvg() {
    std::cout << svg;
}

void Algorithm::setGcodeFilePath(const std::string &path) {
    gcode.setPath(path);
}


void Algorithm::mergeIntersectFigures() {
    if (svg.getFiguresCount() < 2) return;
    fig::Figure *newFig;
    auto end = svg.end();
    for (auto first = svg.begin(); first != end - 1; ++first)
        for (auto second = first + 1; second != end; ++second) {
            if (first == second)
                continue;

            int overlap = isOverlap(*first, *second);
            if (overlap) {
                if (overlap == 1) {
                    svg.erase(second);
                } else if (overlap == 2) {
                    svg.erase(first);
                }
            } //else if (isIntersected(*first, *second)) {
//                newFig = intersect(*fig1, *fig2);
//                delete fig1;
//                delete fig2;
//                fig1 = newFig;
//                fig2 = nullptr;
//            }
        }
}

