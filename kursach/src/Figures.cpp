//
// Created by nektt on 27/11/2022.
//

#include "Figures.h"
#include <algorithm>


/////////////////////////////////////////// GENERAL ///////////////////////////////////////////////

int fig::getNumberFromRegex(const std::regex &reg, const std::string &svgStr) {
    std::smatch match;
    static const std::regex numberR(R"("\d+)");
    std::regex_search(std::cbegin(svgStr), std::cend(svgStr), match, reg);
    if (match.length() == 0) throw std::runtime_error("svg format err");
    std::regex_search(std::cbegin(match[0].str()), std::cend(match[0].str()), match, numberR);
    std::string ss = match[0].str();
    std::string s(std::begin(ss) + 1, std::end(ss));
    return std::stoi(s);
}


std::ostream &operator<<(std::ostream &out, const fig::Point &point) {
    out << "(" << point.x << " : " << point.y << ")";
    return out;
}


bool operator==(const fig::figVariants &left, const fig::figVariants &right) {
    if (left.index() != right.index()) return false;
    switch (left.index()) {
        case fig::CIRCLE:
            return std::get<fig::Circle>(left) == std::get<fig::Circle>(right);
        case fig::LINE:
            return std::get<fig::Line>(left) == std::get<fig::Line>(right);
        case fig::RECT:
            return std::get<fig::Rect>(left) == std::get<fig::Rect>(right);
        case fig::POLYGON:
            return std::get<fig::Polygon>(left) == std::get<fig::Polygon>(right);
        case fig::PATH:
            return std::get<fig::Path>(left) == std::get<fig::Path>(right);
    }
    return false;
}


double fig::getDistance(fig::Point a, fig::Point b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


double fig::getDistance(fig::Line line, fig::Point point) {
    if (line.pointBelongs(point))
        return 0;
    double A = line.getPoint1().y - line.getPoint2().y;
    double B = line.getPoint1().x - line.getPoint2().x;
    double C = line.getPoint1().y * line.getPoint2().x - line.getPoint2().y * line.getPoint1().x;
    double H = (A * point.x + B * point.y + C) / sqrt(A * A + B * B);
    H = H > 0 ? H : -H;
    double d1 = getDistance(point, line.getPoint1()), d2 = getDistance(point, line.getPoint2());

    if (H == 0)
        return std::min(d1, d2);
    return std::min(d1, std::min(d2, H));
}


/////////////////////////////////////////// POINT /////////////////////////////////////////////////

bool fig::Point::operator==(const fig::Point &other) const {
    return x == other.x && y == other.y;
}

bool fig::Point::operator!=(const fig::Point &other) const {
    return x != other.x || y != other.y;
}


/////////////////////////////////////////// CIRCLE ////////////////////////////////////////////////

void fig::Circle::print() const {
    std::cout << "Circle: circle = " << getCenter() << ", r = " << getRadius();
}

void fig::Circle::parseSvg(const std::string &svgStr) {
// Format example:
// <circle cx="150" cy="100" r="80" fill="green" />
//
    std::regex cxR(R"(cx\s*=\s*"\d+")"),
            cyR(R"(cy\s*=\s*"\d+")"), rR(R"(r\s*=\s*"\d+")");

    m_c.x = getNumberFromRegex(cxR, svgStr);
    m_c.y = getNumberFromRegex(cyR, svgStr);
    m_r = getNumberFromRegex(rR, svgStr);
}


// friend

bool fig::operator==(const fig::Circle &left, const fig::Circle &right) {
    return (left.m_c == right.m_c) && (left.m_r == right.m_r);
}

bool fig::doesOverlap(const fig::Circle &left, fig::figVariants rightVariant) {
    switch (rightVariant.index()) {
        case fig::CIRCLE: {
            auto *right = std::get_if<fig::Circle>(&rightVariant);
            double d = fig::getDistance(left.getCenter(), right->getCenter());
            return (left.getRadius() >= right->getRadius()) &&
                   (d + right->getRadius() <= left.getRadius());
        }
        case fig::LINE: {
            auto *right = std::get_if<fig::Line>(&rightVariant);
            bool firstInCircle = left.pointBelongs(right->getPoint1());
            bool secondInCircle = left.pointBelongs(right->getPoint2());

            return firstInCircle && secondInCircle;
        }
        case fig::RECT: {
            auto *right = std::get_if<fig::Rect>(&rightVariant);
            fig::Point p1 = right->getPosition();
            fig::Point p2{p1.x, p1.y + right->getHeight()};
            fig::Point p3{p1.x + right->getWidth(), p1.y};
            fig::Point p4{p1.x + right->getWidth(), p1.y + right->getHeight()};
            return (left.pointBelongs(p1) && left.pointBelongs(p2) && left.pointBelongs(p3) &&
                    left.pointBelongs(p4));
        }
        case fig::PATH: {
            auto *right = std::get_if<fig::Path>(&rightVariant);
            return (std::ranges::all_of((*right).begin(), (*right).end(),
                                        [left](fig::Point p) { return left.pointBelongs(p); }));
        }
        case fig::POLYGON: {
            auto *right = std::get_if<fig::Polygon>(&rightVariant);
            return (std::ranges::all_of((*right).begin(), (*right).end(),
                                        [left](fig::Point p) { return left.pointBelongs(p); }));
        }
    }

}


double fig::getFiguresDistance(const fig::Circle &circle, const figVariants &figV) { //TODO
    switch (figV.index()) {
        case fig::CIRCLE: {
            fig::Circle rCircle = std::get<fig::Circle>(figV);
            double d = getDistance(circle.getCenter(), rCircle.getCenter())
                       - circle.getRadius() - rCircle.getRadius();
            return d < 0 ? 0 : d;
        }
        case fig::LINE: {
            fig::Line line = std::get<fig::Line>(figV);
            // return min distance between circle center and line ends
            // due to the specifics of the drawing algorithm
            return std::min(getDistance(circle.getCenter(), line.getPoint1()),
                            getDistance(circle.getCenter(), line.getPoint2())) - (double) circle.getRadius();

        }
        case fig::RECT: {
            // return min distance between circle center and rectangle sides
            fig::Rect rect = std::get<fig::Rect>(figV);
            fig::Point p1{rect.getPosition()},
                    p2{rect.getPosition().x + rect.getWidth(), rect.getPosition().y},
                    p3{rect.getPosition().x + rect.getWidth(), rect.getPosition().y + rect.getHeight()},
                    p4{rect.getPosition().x, rect.getPosition().y + rect.getHeight()};

            fig::Point trgPoint = circle.getCenter();

            double d[] = {getDistance({p1, p2}, trgPoint), getDistance({p2, p3}, trgPoint),
                          getDistance({p3, p4}, trgPoint), getDistance({p4, p1}, trgPoint)};

            return (*std::min_element(std::begin(d), std::end(d))) - (double) circle.getRadius();
        }
        case fig::POLYGON: {
            fig::Polygon poly = std::get<fig::Polygon>(figV);
            fig::Point trgPoint = circle.getCenter();
            std::vector<double> d;
            d.reserve(poly.getPointsCount());
            for (auto p = poly.begin(); p != poly.end() - 1; ++p)
                d.push_back(getDistance({*p, *(p + 1)}, trgPoint));
            d.push_back(getDistance({*poly.begin(), *(poly.end() - 1)}, trgPoint));

            return (*std::min_element(std::begin(d), std::end(d))) - (double) circle.getRadius();
        }
        case fig::PATH: {
            fig::Path path = std::get<fig::Path>(figV);
            fig::Point trgPoint = circle.getCenter();
            std::vector<double> d;
            d.reserve(path.getPointsCount());
            for (auto p = path.begin(); p != path.end() - 1; ++p)
                d.push_back(getDistance({*p, *(p + 1)}, trgPoint));
            d.push_back(getDistance({*path.begin(), *(path.end() - 1)}, trgPoint));

            return (*std::min_element(std::begin(d), std::end(d))) - (double) circle.getRadius();
        }
    }
    return 0;
}

/////////////////////////////////////////// RECT //////////////////////////////////////////////////

void fig::Rect::parseSvg(const std::string &svgStr) {
// Format example:
// <line x1="0" y1="80" x2="100" y2="20" stroke="black" />
//
    std::regex xR(R"(x\s*=\s*"\d+")"), yR(R"(y\s*=\s*"\d+")"),
            widthR(R"(width\s*=\s*"\d+?")"), heightR(R"(height\s*=\s*"\d+?")");
    std::smatch match;

    m_width = getNumberFromRegex(widthR, svgStr);
    m_height = getNumberFromRegex(heightR, svgStr);

    if (std::regex_search(svgStr, match, xR))
        m_coord.x = getNumberFromRegex(xR, svgStr);
    if (std::regex_search(svgStr, match, yR))
        m_coord.y = getNumberFromRegex(yR, svgStr);

}

void fig::Rect::print() const {
    std::cout << "Rect: pos = " << getPosition() << ", width = " << getWidth() << ", height = " <<
              getHeight();
}


// friend

bool fig::operator==(const fig::Rect &left, const fig::Rect &right) {
    return (left.m_width == right.m_width) && (left.m_height == right.m_height)
           && (left.m_coord == right.m_coord);
}

bool fig::doesOverlap(const fig::Rect &left, fig::figVariants rightVariant) {
    switch (rightVariant.index()) {
        case fig::CIRCLE: {
            auto *right = std::get_if<fig::Circle>(&rightVariant);
            return (left.pointBelongs({right->getCenter().x, right->getCenter().y + right->getRadius()})
                    &&
                    left.pointBelongs({right->getCenter().x, right->getCenter().y - right->getRadius()})
                    &&
                    left.pointBelongs({right->getCenter().x + right->getRadius(), right->getCenter().y})
                    &&
                    left.pointBelongs({right->getCenter().x - right->getRadius(), right->getCenter().y}));
        }
        case fig::RECT: {
            auto *right = std::get_if<fig::Rect>(&rightVariant);
            fig::Point rightCoord = right->getPosition();
            int rHeight = right->getHeight(), rWidth = right->getWidth();
            return (left.pointBelongs(rightCoord) &&
                    left.pointBelongs({rightCoord.x + rWidth, rightCoord.y}) &&
                    left.pointBelongs({rightCoord.x + rWidth, rightCoord.y + rHeight}) &&
                    left.pointBelongs({rightCoord.x, rightCoord.y + rHeight}));
        }
        case fig::LINE: {
            auto *right = std::get_if<fig::Line>(&rightVariant);
            return (left.pointBelongs(right->getPoint1()) && left.pointBelongs(right->getPoint2()));
        }
        case fig::PATH: {
            auto *right = std::get_if<fig::Path>(&rightVariant);
            return (std::ranges::all_of((*right).begin(), (*right).end(),
                                        [left](fig::Point p) { return left.pointBelongs(p); }));
        }
        case fig::POLYGON: {
            auto *right = std::get_if<fig::Polygon>(&rightVariant);
            return (std::ranges::all_of((*right).begin(), (*right).end(),
                                        [left](fig::Point p) { return left.pointBelongs(p); }));

        }

    }


    return false; //TODO implement
}

double fig::getFiguresDistance(const fig::Rect &rect, const fig::figVariants &figV) {
    return 0;  //TODO
}


/////////////////////////////////////////// LINE //////////////////////////////////////////////////

void fig::Line::parseSvg(const std::string &svgStr) {
// Format example:
// <line x1="0" y1="80" x2="100" y2="20" stroke="black" />
//
    std::regex numberR(R"(\d+)"), x1R(R"(x1\s*=\s*"\d+")"),
            x2R(R"(x2\s*=\s*"\d+")"), y1R(R"(y1\s*=\s*"\d+")"), y2R(R"(y2\s*=\s*"\d+")");

    one.x = getNumberFromRegex(x1R, svgStr);
    one.y = getNumberFromRegex(y1R, svgStr);
    two.x = getNumberFromRegex(x2R, svgStr);
    two.y = getNumberFromRegex(y2R, svgStr);
}

void fig::Line::print() const {
    std::cout << "Line: p1 = " << getPoint1() << ", p2 = " << getPoint2();
}


// friend

bool fig::doesOverlap(const fig::Line &left, figVariants rightVariant) {
    switch (rightVariant.index()) {
        case fig::CIRCLE:
            return false;
        case fig::LINE: {
            auto *right = std::get_if<fig::Line>(&rightVariant);
            return left.pointBelongs(right->getPoint1()) && left.pointBelongs(right->getPoint2());
        }
        case fig::RECT: {
            auto *right = std::get_if<fig::Rect>(&rightVariant);
            int rectHeight = right->getHeight(),
                    rectWidth = right->getWidth();
            fig::Point rectPos = right->getPosition();
            if (rectHeight == 0)
                return left.pointBelongs(rectPos) && left.pointBelongs({rectPos.x + rectWidth, rectPos.y});
            else if (rectWidth == 0)
                return left.pointBelongs(rectPos) && left.pointBelongs({rectPos.x, rectPos.y + rectHeight});
            else return false;
        }
        case fig::PATH: {
            auto *right = std::get_if<fig::Path>(&rightVariant);
            return (std::ranges::all_of((*right).begin(), (*right).end(),
                                        [left](fig::Point p) { return left.pointBelongs(p); }));
        }
        case fig::POLYGON: {
            auto *right = std::get_if<fig::Polygon>(&rightVariant);
            return (std::ranges::all_of((*right).begin(), (*right).end(),
                                        [left](fig::Point p) { return left.pointBelongs(p); }));
        }
    }
}


bool fig::operator==(const fig::Line &left, const fig::Line &right) {
    return (left.one == right.one) && (left.two == right.two);
}

double fig::getFiguresDistance(const fig::Line &line, const fig::figVariants &figV) {
    return 0;  //TODO
}


/////////////////////////////////////////// POLYGON //////////////////////////////////////////////////

void fig::Polygon::parseSvg(const std::string &svgStr) {
    std::regex pointsR(R"(\d+,\d+)");
    std::smatch match;

    auto words_begin =
            std::sregex_iterator(svgStr.begin(), svgStr.end(), pointsR);
    auto words_end = std::sregex_iterator();
    if (words_begin == words_end) throw std::runtime_error("svg format error");

    int x, y, sepPos;
    std::string match_str;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        match = *i;
        match_str = match.str();
        sepPos = match_str.find(',');
        x = std::stoi(std::string(match_str.cbegin(), match_str.cbegin() + sepPos));
        y = std::stoi(std::string(match_str.cbegin() + sepPos + 1, match_str.cend()));
        m_points.push_back(fig::Point{x, y});
    }
}

void fig::Polygon::print() const {
    std::cout << "Polygon: points = ";
    for (auto p: m_points)
        std::cout << p << ", ";
}


// friend

bool fig::operator!=(const fig::Polygon &left, const fig::Polygon &right) {
    return !(left == right);
}

bool fig::operator==(const fig::Polygon &left, const fig::Polygon &right) {
    if (left.m_points.size() != right.m_points.size()) return false;
    if (left.m_points.size() == 0) return true;

    auto leftIter = left.m_points.cbegin();
    auto rightIter = right.m_points.cbegin();
    for (; rightIter != right.m_points.cend(); ++rightIter)
        if (*rightIter == *leftIter) break;

    if (rightIter == right.m_points.cend())
        return false;

    for (; leftIter + 1 != left.m_points.cend();) {
        ++leftIter;
        if (rightIter + 1 == right.m_points.cend())
            rightIter = right.m_points.cbegin();
        else ++rightIter;

        if (*rightIter != *leftIter) return false;
    }
    return true;
}

bool fig::doesOverlap(const fig::Polygon &left, const fig::figVariants &right) {
    return false; //TODO implement
}

double fig::getFiguresDistance(const fig::Polygon &polygon, const fig::figVariants &figV) {
    return 0; //TODO
}

/////////////////////////////////////////// PATH //////////////////////////////////////////////////

void fig::Path::parseSvg(const std::string &svgStr) {
    std::regex pointsR(R"(\d+,\d+)");
    std::smatch match;

    auto words_begin =
            std::sregex_iterator(svgStr.begin(), svgStr.end(), pointsR);
    auto words_end = std::sregex_iterator();
    if (words_begin == words_end) throw std::runtime_error("svg format error");

    int x, y, sepPos;
    std::string match_str;
    Point firstP;
    bool isFirst = true;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        match = *i;
        match_str = match.str();
        sepPos = match_str.find(',');
        x = std::stoi(std::string(match_str.cbegin(), match_str.cbegin() + sepPos));
        y = std::stoi(std::string(match_str.cbegin() + sepPos + 1, match_str.cend()));
        m_points.push_back(fig::Point{x, y});
        if (isFirst) {
            firstP = fig::Point{x, y};
            isFirst = false;
        }
    }
    if (m_fromPolygon)
        m_points.push_back(firstP);
}

void fig::Path::print() const {
    std::cout << "Path: points = ";
    for (auto p: m_points)
        std::cout << p << ", ";
}


// friend

bool fig::operator==(const fig::Path &left, const fig::Path &right) {
    if (left.m_points.size() != right.m_points.size()) return false;
    for (auto l = left.m_points.cbegin(), r = right.m_points.cbegin();
         l != left.m_points.cend() && r != right.m_points.cend(); ++r, ++l) {
        if (!(*l == *r)) return false;
    }
    return true;
}

bool fig::doesOverlap(const fig::Path &left, const fig::figVariants &rightVariant) {
    switch (rightVariant.index()) {
        case fig::CIRCLE:
            return false;
        case fig::LINE: {
            auto *right = std::get_if<fig::Line>(&rightVariant);

            for (auto it = left.begin(); it != left.end() - 1; ++it) {
                fig::Line seg{*it, *(it + 1)};
                if (doesOverlap(seg, *right))
                    return true;
            }
            return false;
        }
        case fig::RECT: {
            auto *right = std::get_if<fig::Rect>(&rightVariant);
            int rectHeight = right->getHeight(),
                    rectWidth = right->getWidth();
            fig::Point rectPos = right->getPosition();
            if (rectHeight == 0)
                return doesOverlap(left, fig::Line(rectPos, {rectPos.x + rectWidth, rectPos.y}));
            else if (rectWidth == 0)
                return doesOverlap(left, fig::Line(rectPos, {rectPos.x, rectPos.y + rectHeight}));
            else return false;
        }
        case fig::PATH: {
            auto *right = std::get_if<fig::Path>(&rightVariant);
            // TODO: implement
            throw std::runtime_error("not implemented");
        }
        case fig::POLYGON: {
            auto *right = std::get_if<fig::Polygon>(&rightVariant);
            // TODO: implement
            throw std::runtime_error("not implemented");
            // return true if the polygon is degenerate into a overlaped line
        }
    }
}

double fig::getFiguresDistance(const fig::Path &path, const fig::figVariants &figV) {
    return 0;  //TODO
}
