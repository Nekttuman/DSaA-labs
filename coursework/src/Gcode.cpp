//
// Created by nektt on 12/4/2022.
//

#include "Gcode.h"


void Gcode::setPrinterSettings(double maxXPos, double maxYPos, double offsetX, double offsetY) {
    if (maxXPos <= offsetX || maxYPos <= offsetY)
        throw;
    maxYPos_m = maxYPos;
    maxXPos_m = maxXPos;
    brushOffsetX_m = offsetX;
    brushOffsetY_m = offsetY;
}

void Gcode::setSvgResolution(double svgResolutionX, double svgResolutionY) {
    svgResolutionX_m = svgResolutionX;
    svgResolutionY_m = svgResolutionY;
}

void Gcode::insertInitGcode() {
    xKoeff = (maxXPos_m - brushOffsetX_m) / svgResolutionX_m;
    yKoeff = (maxYPos_m - brushOffsetY_m) / svgResolutionY_m;
    file << "G28 ; calibration\n";
    file << "G1 X" + std::to_string(brushOffsetX_m + 0.3) << "Z3 F5000.0 \n";
    file << "G1 X" + std::to_string(brushOffsetX_m + 0.3) + " Y" + std::to_string(brushOffsetY_m + 0.3) +
            " Z0 F5000.0 ; Move to start position\n";
}

void Gcode::moveToStart() {
    file << "\n\nG1 X" + std::to_string(brushOffsetX_m) + " Y" + std::to_string(brushOffsetY_m) +
            " Z0 F5000.0\n";
}

void Gcode::moveToEnd() {
    file << "\n\nG1 X" + std::to_string(brushOffsetX_m) + " Y" + std::to_string(brushOffsetY_m) +
            " F5000.0\nG1 X0 Y0\n\n";
}

void Gcode::raiseBrush() {
    file << "G1 Z5 F3000\n";
}

void Gcode::lowerBrush() {
    file << "G1 Z0 F3000\n";
}

void Gcode::moveTo(fig::Point p) {
    raiseBrush();
    file << "; move to point (" << p.x << ":" << p.y << ")\n"
         << "G1 X" << maxXPos_m - p.x * xKoeff << " Y" << maxYPos_m - p.y * yKoeff << " F3000\n";
    lowerBrush();

}

void Gcode::drawTo(fig::Point p) {
    file << "G1 X" << maxXPos_m - p.x * xKoeff << " Y" << maxYPos_m - p.y * yKoeff << " F3000; draw\n";
}

void Gcode::sliceFig(const fig::slicedFig &fig) {
    switch (fig.ft) {
        case fig::CIRCLE: {
            file << "\n;CIRCLE\n";
            moveTo(fig.points.front());
            for (auto i = ++fig.points.begin(); i != fig.points.end(); ++i)
                drawTo(*i);
            break;
        }
        case fig::SEGMENT: {
            file << "\n;SEGMENT\n";
            moveTo(fig.startP);
            drawTo(fig.endP);
            break;
        }
        case fig::RECT: {
            file << "\n;RECT\n";
            moveTo(fig.points.front());
            for (auto i = ++fig.points.begin(); i != fig.points.end(); ++i)
                drawTo(*i);
            break;
        }
        case fig::PATH: {

        }
        case fig::POLYGON: {

        }
    }
}

void Gcode::generateGcode(const std::string &path, const std::vector<fig::slicedFig> &figures) {
    m_pathToFile = path;
    file.open(path, std::ios_base::out);
    if (!file.is_open())
        throw std::runtime_error("gcode file didnt open: " + path);
    insertInitGcode();

    for (const auto &fig: figures)
        sliceFig(fig);

    raiseBrush();
    moveToEnd();
    file.close();
}