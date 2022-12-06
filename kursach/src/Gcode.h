//
// Created by nektt on 12/4/2022.
//

#ifndef MAIN_CPP_GCODE_H
#define MAIN_CPP_GCODE_H

#include <string>
#include <fstream>

class Gcode {
    std::string m_pathToFile;
public:
    Gcode() = default;

    Gcode(const std::string &path) : m_pathToFile(path) {}

    void setPath(const std::string &path) { m_pathToFile = path; }


};


#endif //MAIN_CPP_GCODE_H
