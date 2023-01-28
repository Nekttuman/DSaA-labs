//
// Created by nektt on 12/4/2022.
//

#include "Gcode.h"


void Gcode::setPrinterSettings(double maxXPos, double maxYPos, double offsetX, double offsetY){
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

