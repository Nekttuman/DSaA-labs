//
// Created by nektt on 27/11/2022.
//

#include "Svg.h"
//#include <SFML/Graphics.hpp>


Svg::Svg(const std::string &path) {
    std::fstream in(path, std::ios_base::in);
    if (!in.is_open()) throw std::invalid_argument("file not opened");

    try { parse(in); }
    catch (const std::exception &e) {
        std::cerr << "PARSE ERROR: " << e.what() << "\n";
    }

    in.close();
}

// TODO: config cmakeLists for sfml work via wsl
//bool Svg::draw() {
//    sf::RenderWindow App(sf::VideoMode(m_width, m_height), "parsed svg", sf::Style::Close);
//    sf::Event Event;
//
//    while (true) {
//        //Verifying events
//        while (App.pollEvent(Event)) {
//            // Window closed
//            if (Event.type == sf::Event::Closed) {
//                return false;
//            }
//
//            //Clearing screen
//            App.clear(sf::Color::White);
//
//            //Drawing
//
//            App.display();
//        }
//
//    }
//}


bool Svg::parseElem(const std::string &elemStr) {
    // TODO parse Circle Ellipse and rect with fill="None" as Path
    std::smatch match;
    const static std::regex circleR(R"(^<circle.+?\/>)"), lineR(R"(^<line.+?\/>)"),
            rectR(R"(^<rect.+?\/>)"), polylineR(R"(^<polyline.+?\/>)"),
            polygonR(R"(^<polygon.+?\/>)"), fillNoneR(R"(fill\s*=\s*"none")");

    if (std::regex_match(elemStr, match, circleR)) {
        m_figures.emplace_back(fig::Circle());
        std::get<fig::Circle>(m_figures.back()).parseSvg(elemStr);
    } else if (std::regex_match(elemStr, match, lineR)) {
        m_figures.emplace_back(fig::Line());
        std::get<fig::Line>(m_figures.back()).parseSvg(elemStr);
    } else if (std::regex_match(elemStr, match, rectR)) {
        m_figures.emplace_back(fig::Rect());
        std::get<fig::Rect>(m_figures.back()).parseSvg(elemStr);
    } else if (std::regex_match(elemStr, match, polylineR) ||
               std::regex_match(elemStr, match, polygonR))
        if (std::regex_search(elemStr, match, fillNoneR)) {
            m_figures.emplace_back(fig::Path(true));

            std::get<fig::Path>(m_figures.back()).parseSvg(elemStr);
        } else {
            m_figures.emplace_back(fig::Polygon());

            std::get<fig::Polygon>(m_figures.back()).parseSvg(elemStr);
        }
    else
        return false;

    return true;
}


void Svg::parse(std::fstream &in) {
    std::string buffer, tmp = "0";
    while (!in.eof()) {
        in >> tmp;
        buffer += tmp + " ";
    }
    auto bufferIter = std::cbegin(buffer);

    std::regex svgTagR(R"(<svg.*?>)"),
            widthR(R"(width\s*=\s*"\d+?")"),
            heightR(R"(height\s*=\s*"\d+?")"),
            numberR(R"(\d+)");


    std::smatch match;
    std::regex_search(bufferIter, std::cend(buffer), match, svgTagR);
    bufferIter += match.position() + match.length();


    // getting svg tag as string
    if (bufferIter == std::cend(buffer)) throw std::runtime_error("svg tag not found");
    std::string svgTagStr = match[0];

    // getting width from <svg ...>
    std::regex_search(std::cbegin(svgTagStr), std::cend(svgTagStr), match, widthR);
    if (match.length() == 0) throw std::runtime_error("svg tag does not contain width");
    std::regex_search(std::cbegin(match[0].str()), std::cend(match[0].str()), match, numberR);
    if (match.length() == 0) throw std::runtime_error("svg tag width format err");

    m_width = std::stoi(match[0].str());

    // getting height from <svg ...>
    std::regex_search(std::cbegin(svgTagStr), std::cend(svgTagStr), match, heightR);
    if (match.length() == 0) throw std::runtime_error("svg tag does not contain height");
    std::regex_search(std::cbegin(match[0].str()), std::cend(match[0].str()), match, numberR);
    if (match.length() == 0) throw std::runtime_error("svg tag height format err");

    m_height = std::stoi(match[0].str());

    std::regex svgTagEndR(R"(.+?<\/svg>)");
    std::regex_search(bufferIter, std::cend(buffer), match, svgTagEndR);
    if (match.length() == 0) throw std::runtime_error("closing svg tag not found");
    buffer = match[0].str().erase(match[0].str().find("</svg>"));

    // parse allElementsStr (buffer) to std::vector<fig::Figure> m_figures
    bufferIter = std::cbegin(buffer);
    std::string elemStr;
    std::regex elemR(R"(<.+?\>)");
    while (std::regex_search(bufferIter, std::cend(buffer), match, elemR)) {
        parseElem(match[0]);
        bufferIter += match.position() + match.length();
    }

    removeDoubles();
}


void Svg::parse(const std::string &path) {
    std::fstream in(path, std::ios_base::in);
    if (!in.is_open()) throw std::invalid_argument("file not opened");

    try { parse(in); }
    catch (const std::exception &e) {
        std::cerr << "PARSE ERROR: " << e.what() << "\n";
    }

    in.close();
    removeDoubles();
}

void Svg::empty() {
    m_figures.clear();
    m_height = 0;
    m_width = 0;
}


std::ostream &operator<<(std::ostream &out, const Svg &svg) {
    std::cout << "\nSVG\n\theight = " << svg.m_height << "\n\twidth = " << svg.m_width << "\n";

    for (const auto &fig: svg.m_figures) {
        std::cout << "\n";

        switch (fig.index()) {      //TODO: find a better solution
            case fig::CIRCLE:
                std::get<fig::Circle>(fig).print();
                break;
            case fig::LINE:
                std::get<fig::Line>(fig).print();
                break;
            case fig::RECT:
                std::get<fig::Rect>(fig).print();
                break;
            case fig::POLYGON:
                std::get<fig::Polygon>(fig).print();
                break;
            case fig::PATH:
                std::get<fig::Path>(fig).print();
                break;
        }
    }
    std::cout << "\n\n";
    return out;
}

void Svg::erase(std::vector<fig::figVariants>::iterator iter) {
    m_figures.erase(iter);
}

////////////////////////////////// PRIVATE METHODS ////////////////////////////////////////////////

void Svg::removeDoubles() {
    auto end = std::cend(m_figures);
    for (auto i = std::cbegin(m_figures); i != end; ++i)
        for (auto j = i + 1; j != end; ++j)
            if (*i == *j)
                m_figures.erase(j);
}


