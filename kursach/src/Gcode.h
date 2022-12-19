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

    int brushOffsetX = 70, brushOffsetY = 60;
    double maxYPos = 235, maxXPos = 235;  // 235-brushOffset
public:
    Gcode() = default;

    void insertInitGcode() {
        file << "G28 ; calibration\n";
        file<<"G1 X" + std::to_string(brushOffsetX + 0.3) <<"Z3 F5000.0 \n";
        file << "G1 X" + std::to_string(brushOffsetX + 0.3) + " Y" + std::to_string(brushOffsetY + 0.3) +
                " Z0 F5000.0 ; Move to start position\n";

    }

    void moveToStart() {
        file << "\n\nG1 X" + std::to_string(brushOffsetX) + " Y" + std::to_string(brushOffsetY) +
                " Z0 F5000.0\n";
    }
    void moveToEnd() {
        file << "\n\nG1 X" + std::to_string(brushOffsetX) + " Y" + std::to_string(brushOffsetY) +
                " F5000.0\nG1 X0 Y0\n\n";
    }

    void raiseBrush() {
        file << "G1 Z5 F3000\n";
    }

    void lowerBrush() {
        file << "G1 Z0 F3000\n";
    }

    void moveTo(fig::Point p) {
        raiseBrush();
        file << "; move to point (" << p.x << ":" << p.y << ")\n"
             << "G1 X" << maxXPos - (p.x) << " Y" << maxYPos - p.y << " F3000\n";
        lowerBrush();

    }

    void drawTo(fig::Point p) {
        file << "G1 X" <<maxXPos - (p.x) << " Y" << maxYPos - p.y << " F3000; draw\n";
    }

    void sliceFig(const fig::slicedFig &fig) {
        switch (fig.ft) {
            case fig::CIRCLE: {
                file<<"\n;CIRCLE\n";
                moveTo(fig.points.front());
                for (auto i = ++fig.points.begin();i != fig.points.end();++i)
                    drawTo(*i);
                break;
            }
            case fig::SEGMENT: {
                file<<"\n;SEGMENT\n";
                moveTo(fig.startP);
                drawTo(fig.endP);
                break;
            }
            case fig::RECT: {
                file<<"\n;RECT\n";
                moveTo(fig.points.front());
                for (auto i = ++fig.points.begin();i != fig.points.end();++i)
                    drawTo(*i);
                break;
            }
            case fig::PATH: {

            }
            case fig::POLYGON: {

            }
        }
    }

    void generateGcode(const std::string &path, const std::vector<fig::slicedFig> &figures) {
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

};


#endif //MAIN_CPP_GCODE_H
