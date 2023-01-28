//
// Created by nektt on 12/4/2022.
//

#ifndef MAIN_CPP_GCODE_H
#define MAIN_CPP_GCODE_H

#include <string>
#include <fstream>

#include "Figures.h"

class Gcode {
    std::string m_pathToFile;

    std::fstream file;

    double brushOffsetX_m = 70, brushOffsetY_m = 60;
    double maxYPos_m = 235, maxXPos_m = 235;  // 235-brushOffset
    double svgResolutionX_m = 800, svgResolutionY_m = 600;
    double xKoeff, yKoeff;
public:
    Gcode() = default;

    void setPrinterSettings(double maxXPos, double maxYPos, double offsetX, double offsetY);

    void setSvgResolution(double svgResolutionX, double svgResolutionY);

    void insertInitGcode();

    void moveToStart();

    void moveToEnd();

    void raiseBrush();

    void lowerBrush();

    void moveTo(fig::Point p);

    void drawTo(fig::Point p);

    void sliceFig(const fig::slicedFig &fig);

    void generateGcode(const std::string &path, const std::vector<fig::slicedFig> &figures);
};


#endif //MAIN_CPP_GCODE_H
