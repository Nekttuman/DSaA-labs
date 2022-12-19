//
// Created by nektt on 27/11/2022.
//

#ifndef MAIN_CPP_SVG_H
#define MAIN_CPP_SVG_H

#include <fstream>
#include <vector>
#include <execution>
#include <iostream>
#include <variant>
#include "Figures.h"

class Svg {
protected:
    std::vector<fig::figVariants> m_figures;

    int m_height, m_width;
public:

    Svg() = default;

    explicit Svg(const std::string &path);

    bool parseElem(const std::string &);

    void parse(std::fstream &in);

    void parse(const std::string &path);

    unsigned getFiguresCount() { return m_figures.size(); }

    int getHeight() { return m_height; }

    int getWidth() { return m_width; }

    void empty();

    // TODO: create decent iterator
    auto begin() { return std::begin(m_figures); }

    auto end() { return std::end(m_figures); }

    fig::figVariants get(unsigned n) { return m_figures[n]; }


    void erase(std::vector<fig::figVariants>::iterator iter);

    // bool draw(); TODO: sfml or qt visualisation

    friend std::ostream &operator<<(std::ostream &out, const Svg &svg);

private:
    void removeDoubles();
};

#endif //MAIN_CPP_SVG_H
