//
// Created by nektt on 12/4/2022.
//

#include "Algorithm.h"


//////////////////////////////////////// FUNCTIONS ////////////////////////////////////////////////

int doesOverlap(const fig::figVariants &left, const fig::figVariants &right) {
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

bool doesIntersect(const fig::figVariants &left, const fig::figVariants &right){
    return false; //TODO: implement alg intersect detecting
}


fig::figVariants intersect(const fig::figVariants &left, const fig::figVariants &right){
    return fig::Circle(0,0,10); //TODO: implement alg intersect
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
    fig::figVariants newFig;
    auto end = svg.end();
    for (auto first = svg.begin(); first != end - 1; ++first)
        for (auto second = svg.begin()+1; second != end; ++second) {
            if (first == second)
                continue;

            int overlap = doesOverlap(*first, *second);
            if (overlap) {
                svg.erase(second);

            } else if (doesIntersect(*first, *second)) {
                newFig = intersect(*first, *second);
                svg.erase(second);
                *first = newFig;
            }
        }
}



double getFiguresDistance(fig::figVariants figV1, fig::figVariants figV2){
    switch (figV1.index()) {
        case fig::CIRCLE:
            return getFiguresDistance(std::get<fig::Circle>(figV1), figV2);
        case fig::LINE:
            return getFiguresDistance(std::get<fig::Line>(figV1), figV2);
        case fig::RECT:
            return getFiguresDistance(std::get<fig::Rect>(figV1), figV2);
        case fig::POLYGON:
            return getFiguresDistance(std::get<fig::Polygon>(figV1), figV2);
        case fig::PATH:
            return getFiguresDistance(std::get<fig::Path>(figV1), figV2);
    }
}



void Algorithm::setFiguresDrawingOrder(){
    double weights[svg.getFiguresCount()][svg.getFiguresCount()];

    int i=0,j=0;
    for (auto fig1 = svg.begin(); fig1 != svg.end(); ++fig1, ++i)
        for (auto fig2 = svg.begin(); fig2 != svg.end(); ++fig2, ++j)
            weights[i][j] = getFiguresDistance(*fig1, *fig2);


}


void Algorithm::sliceFigures() {
    for (auto figVariant = svg.begin(); figVariant != svg.end(); ++figVariant){
        switch (figVariant->index()) {
            case fig::CIRCLE:

            case fig::LINE:

            case fig::RECT:

            case fig::POLYGON:

            case fig::PATH:

                break;
        }

    }

}

