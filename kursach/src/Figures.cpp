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
        case fig::SEGMENT:
            return std::get<fig::Segment>(left) == std::get<fig::Segment>(right);
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


double fig::getDistance(const Segment &line, fig::Point point) {
    if (line.pointBelongs(point))
        return 0;
    double A = line.getPoint1().y - line.getPoint2().y;
    double B = line.getPoint1().x - line.getPoint2().x;
    double C = line.getPoint1().y * line.getPoint2().x - line.getPoint2().y * line.getPoint1().x;
    double H = (A * point.x + B * point.y + C) / sqrt(A * A + B * B);
    H = H > 0 ? H : -H;
    double d1 = getDistance(point, line.getPoint1()),
            d2 = getDistance(point, line.getPoint2());

    if (H == 0) // point belongs line, but doesnt belong segment
        return std::min(d1, d2);
    return std::min(d1, std::min(d2, H));
}


/////////////////////////////////////////// POINT /////////////////////////////////////////////////

bool fig::Point::operator==(const fig::Point &other) const {
    return (x == other.x && y == other.y);
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
        case fig::SEGMENT: {
            auto *right = std::get_if<fig::Segment>(&rightVariant);
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
    return false;
}


double fig::getFiguresDistance(const fig::Circle &circle, const figVariants &figV) { //TODO
    switch (figV.index()) {
        case fig::CIRCLE: {
            fig::Circle rCircle = std::get<fig::Circle>(figV);
            double d = getDistance(circle.getCenter(), rCircle.getCenter())
                       - circle.getRadius() - rCircle.getRadius();
            return d < 0 ? 0 : d;
        }
        case fig::SEGMENT: {
            fig::Segment line = std::get<fig::Segment>(figV);
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
                    p3{rect.getPosition().x + rect.getWidth(), rect.getPosition().y - rect.getHeight()},
                    p4{rect.getPosition().x, rect.getPosition().y - rect.getHeight()};

            fig::Point trgtPoint = circle.getCenter();
            int circleRadius = circle.getRadius();

            fig::Segment lines[] = {{p1, p2},
                                    {p2, p3},
                                    {p3, p4},
                                    {p4, p1}};
            double d[4];
            double ds;
            for (int i = 0; i < 4; ++i) {
                ds = getDistance(lines[i], trgtPoint);
                if (ds <= circleRadius)
                    d[i] = std::min(getDistance(lines[i].getPoint1(), trgtPoint),
                                    getDistance(lines[i].getPoint2(), trgtPoint));
                else
                    d[i] = ds;
            }

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


fig::Point getNearestPointForCircleAndPoint(const fig::Circle &circle, const fig::Point &point) {
    double x0 = circle.getCenter().x, y0 = circle.getCenter().y, r = circle.getRadius();
    double x1 = point.x, y1 = point.y;

    double k, b;
    if (x0 - x1 != 0) {
        k = (y0 - y1) / (x0 - x1);
        b = -x1 * (y0 - y1) / (x0 - x1) + y1;
    } else {
        double Y = y0 + ((y1 > y0) ? +r : -r);

        return {x0, Y};
    }

    double A = (k * k + 1),
            B = 2 * (k * b - k * y0 - x0),
            C = b * b + y0 * y0 + x0 * x0 - r * r - 2 * b * y0;

    double D = B * B - 4 * A * C;

    double X1, Y1, X2, Y2;
    if (A != 0) {
        X1 = (-B - sqrt(D)) / (2 * A);
        X2 = (-B + sqrt(D)) / (2 * A);
    } else {
        X1 = -C / B;
        X2 = -C / B;
    }
    Y1 = k * X1 + b;
    Y2 = k * X2 + b;

    if (fig::Segment(circle.getCenter(), point).pointBelongs({X1, Y1}))
        return {X1, Y1};
    return {X2, Y2};
}

#include <float.h>

fig::Point fig::Circle::getNearestPoint(const fig::figVariants &figVariant) const {
    switch (figVariant.index()) {
        case fig::CIRCLE: {
            fig::Circle circle = std::get<fig::Circle>(figVariant);
            return getNearestPointForCircleAndPoint(*this, circle.getCenter());

        }
        case fig::SEGMENT: {
            fig::Segment segment = std::get<fig::Segment>(figVariant);
            fig::Point minP;
            if (getDistance(m_c, segment.getPoint1()) < getDistance(m_c, segment.getPoint2()))
                minP = segment.getPoint1();
            else
                minP = segment.getPoint2();
            return getNearestPointForCircleAndPoint(*this, minP);
        }
        case fig::RECT: {
            fig::Rect rect = std::get<fig::Rect>(figVariant);

            fig::Point rectVerts[] = {
                    rect.getPosition(),
                    {rect.getPosition().x, rect.getPosition().y + rect.getHeight()},
                    {rect.getPosition().x + rect.getWidth(), rect.getPosition().y},
                    {rect.getPosition().x + rect.getWidth(), rect.getPosition().y + rect.getHeight()},
            };

            auto minDist = DBL_MAX;
            fig::Point nearestPoint;
            for (auto v: rectVerts) {
                if (getDistance(m_c, v) < minDist) {
                    minDist = getDistance(m_c, v);
                    nearestPoint = v;
                }
            };

            return getNearestPointForCircleAndPoint(*this, nearestPoint);
        }

        case fig::POLYGON:

        case fig::PATH:

            break;
    }


    return {}; //TODO
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
        case fig::SEGMENT: {
            auto *right = std::get_if<fig::Segment>(&rightVariant);
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


fig::Point fig::Rect::getNearestPoint(const fig::figVariants &figV) const {
    switch (figV.index()) {
        case fig::CIRCLE: {
            fig::Circle circle = std::get<fig::Circle>(figV);

            fig::Point rectVerts[] = {
                    getPosition(),
                    {getPosition().x, getPosition().y + getHeight()},
                    {getPosition().x + getWidth(), getPosition().y},
                    {getPosition().x + getWidth(), getPosition().y + getHeight()},
            };

            auto minDist = DBL_MAX;
            fig::Point nearestPoint;
            for (auto v: rectVerts) {
                if (getDistance(circle.getCenter(), v) < minDist) {
                    minDist = getDistance(circle.getCenter(), v);
                    nearestPoint = v;
                }
            };

            return nearestPoint;
        }
        case fig::SEGMENT: {
            fig::Segment segment = std::get<fig::Segment>(figV);
            fig::Point rectVerts[] = {
                    getPosition(),
                    {getPosition().x, getPosition().y + getHeight()},
                    {getPosition().x + getWidth(), getPosition().y},
                    {getPosition().x + getWidth(), getPosition().y + getHeight()},
            };
            fig::Point segmentVerts[] = {
                    segment.getPoint1(),
                    segment.getPoint2()};

            auto minDist = DBL_MAX;
            fig::Point nearestPoint;
            for (auto vS: segmentVerts) {
                for (auto vR: rectVerts) {
                    if (getDistance(vS, vR) < minDist) {
                        minDist = getDistance(vS, vR);
                        nearestPoint = vR;
                    }
                }
            }

            return nearestPoint;
        }
        case fig::RECT: {
            fig::Rect rect = std::get<fig::Rect>(figV);

            fig::Point lRectVerts[] = {
                    m_coord,
                    {m_coord.x, m_coord.y + getHeight()},
                    {m_coord.x + getWidth(), m_coord.y},
                    {m_coord.x + getWidth(), m_coord.y + getHeight()},
            };
            fig::Point rRectVerts[] = {
                    rect.getPosition(),
                    {rect.getPosition().x, rect.getPosition().y + rect.getHeight()},
                    {rect.getPosition().x + rect.getWidth(), rect.getPosition().y},
                    {rect.getPosition().x + rect.getWidth(), rect.getPosition().y + getHeight()},
            };

            auto minDist = DBL_MAX;
            fig::Point nearestPoint;
            for (auto vS: rRectVerts) {
                for (auto vR: lRectVerts) {
                    if (getDistance(vS, vR) < minDist) {
                        minDist = getDistance(vS, vR);
                        nearestPoint = vR;
                    }
                }
            }

            return nearestPoint;
        }

        case fig::POLYGON:

        case fig::PATH:

            break;
    }


    return {}; //TODO

}

double fig::getFiguresDistance(const fig::Rect &lRect, const fig::figVariants &figV) {
    switch (figV.index()) {
        case fig::CIRCLE: {
            fig::Circle circle = std::get<fig::Circle>(figV);
            return getDistance(lRect.getNearestPoint(circle), circle.getNearestPoint(lRect));
        }
        case fig::SEGMENT: {
            fig::Segment segment = std::get<fig::Segment>(figV);
            fig::Point p1 = lRect.getNearestPoint(segment), p2 = segment.getNearestPoint(lRect);
            return getDistance(p1, p2);
        }
        case fig::RECT: {
            fig::Rect rRect = std::get<fig::Rect>(figV);
            fig::Point p1 = lRect.getNearestPoint(rRect), p2 = rRect.getNearestPoint(lRect);
            return getDistance(p1, p2);
        }

        case fig::POLYGON:

        case fig::PATH:

            break;
    }

    return 0;  //TODO
}


/////////////////////////////////////////// LINE SEGMENT //////////////////////////////////////////

void fig::Segment::parseSvg(const std::string &svgStr) {
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

void fig::Segment::print() const {
    std::cout << "Line: p1 = " << getPoint1() << ", p2 = " << getPoint2();
}


// friend

bool fig::doesOverlap(const fig::Segment &left, figVariants rightVariant) {
    switch (rightVariant.index()) {
        case fig::CIRCLE:
            return false;
        case fig::SEGMENT: {
            auto *right = std::get_if<fig::Segment>(&rightVariant);
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
    return false;
}


bool fig::operator==(const fig::Segment &left, const fig::Segment &right) {
    return (left.one == right.one) && (left.two == right.two);
}

double fig::getFiguresDistance(const fig::Segment &seg, const fig::figVariants &figV) {
    switch (figV.index()) {
        case fig::CIRCLE: { //TODO test
            fig::Circle circle = std::get<fig::Circle>(figV);
            double d1 = getDistance(circle.getCenter(), seg.getPoint1())
                        - circle.getRadius();
            d1 = d1 < 0 ? 0 : d1;
            double d2 = getDistance(circle.getCenter(), seg.getPoint2())
                        - circle.getRadius();
            d2 = d2 < 0 ? 0 : d2;
            return d2 < d1 ? d2 : d1;
        }
        case fig::SEGMENT: {
            fig::Segment rSeg = std::get<fig::Segment>(figV);

            std::vector<double> d = {
                    getDistance(seg.getPoint1(), rSeg.getPoint1()),
                    getDistance(seg.getPoint1(), rSeg.getPoint2()),
                    getDistance(seg.getPoint2(), rSeg.getPoint1()),
                    getDistance(seg.getPoint2(), rSeg.getPoint2()),
            };

            return *std::min_element(d.begin(), d.end());

        }
        case fig::RECT: {
            fig::Rect rect = std::get<fig::Rect>(figV);

            return getFiguresDistance(rect, seg);

        }
        case fig::POLYGON: {

        }
        case fig::PATH: {

        }
    }
    return 0;  //TODO
}

fig::Point fig::Segment::getNearestPoint(const fig::figVariants &figV) const {
    switch (figV.index()) {
        case fig::CIRCLE: {
            fig::Circle circle = std::get<fig::Circle>(figV);
            if (getDistance(circle.getCenter(), getPoint1()) < getDistance(circle.getCenter(), getPoint2()))
                return getPoint1();
            return getPoint2();
        }
        case fig::SEGMENT: {
            fig::Segment rSeg = std::get<fig::Segment>(figV);

            std::vector<double> d = {
                    getDistance(getPoint1(), rSeg.getPoint1()),
                    getDistance(getPoint1(), rSeg.getPoint2()),
                    getDistance(getPoint2(), rSeg.getPoint1()),
                    getDistance(getPoint2(), rSeg.getPoint2()),
            };
            double minE = *std::min_element(d.begin(), d.end());
            if (minE == d[0] || minE == d[1])
                return getPoint1();
            return getPoint2();
        }
        case fig::RECT: {
            fig::Rect rect = std::get<fig::Rect>(figV);
            fig::Point rectVerts[] = {
                    rect.getPosition(),
                    {rect.getPosition().x, rect.getPosition().y + rect.getHeight()},
                    {rect.getPosition().x + rect.getWidth(), rect.getPosition().y},
                    {rect.getPosition().x + rect.getWidth(), rect.getPosition().y + rect.getHeight()},
            };
            fig::Point segmentVerts[] = {
                    getPoint1(),
                    getPoint2()};

            auto minDist = DBL_MAX;
            fig::Point nearestPoint;
            for (auto vS: segmentVerts) {
                for (auto vR: rectVerts) {
                    if (getDistance(vS, vR) < minDist) {
                        minDist = getDistance(vS, vR);
                        nearestPoint = vS;
                    }
                }
            }

            return nearestPoint;
        }
    }
    return {};
}


/////////////////////////////////////////// POLYGON //////////////////////////////////////////////////

void fig::Polygon::parseSvg(const std::string &svgStr) {
    std::regex pointsR(R"(\d+,\d+)");
    std::smatch match;

    auto words_begin =
            std::sregex_iterator(svgStr.begin(), svgStr.end(), pointsR);
    auto words_end = std::sregex_iterator();
    if (words_begin == words_end) throw std::runtime_error("svg format error");

    double x, y;
    unsigned sepPos;
    std::string match_str;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        match = *i;
        match_str = match.str();
        sepPos = match_str.find(',');
        x = std::stoi(std::string(match_str.cbegin(), match_str.cbegin() + sepPos));
        y = std::stoi(std::string(match_str.cbegin() + sepPos + 1, match_str.cend()));
        m_points.push_back({x, y});
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
    if (left.m_points.empty()) return true;

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

fig::Point fig::Polygon::getNearestPoint(const fig::figVariants &fig) const {
    return {}; //TODO
}

/////////////////////////////////////////// PATH //////////////////////////////////////////////////

void fig::Path::parseSvg(const std::string &svgStr) {
    std::regex pointsR(R"(\d+,\d+)");
    std::smatch match;

    auto words_begin =
            std::sregex_iterator(svgStr.begin(), svgStr.end(), pointsR);
    auto words_end = std::sregex_iterator();
    if (words_begin == words_end) throw std::runtime_error("svg format error");

    double x, y;
    unsigned sepPos;
    std::string match_str;
    Point firstP;
    bool isFirst = true;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        match = *i;
        match_str = match.str();
        sepPos = match_str.find(',');
        x = std::stoi(std::string(match_str.cbegin(), match_str.cbegin() + sepPos));
        y = std::stoi(std::string(match_str.cbegin() + sepPos + 1, match_str.cend()));
        m_points.push_back({x, y});
        if (isFirst) {
            firstP = {x, y};
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
        case fig::SEGMENT: {
            auto *right = std::get_if<fig::Segment>(&rightVariant);

            for (auto it = left.begin(); it != left.end() - 1; ++it) {
                fig::Segment seg{*it, *(it + 1)};
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
                return doesOverlap(left, fig::Segment(rectPos, {rectPos.x + rectWidth, rectPos.y}));
            else if (rectWidth == 0)
                return doesOverlap(left, fig::Segment(rectPos, {rectPos.x, rectPos.y + rectHeight}));
            else return false;
        }
//        case fig::PATH: {
////            auto *right = std::get_if<fig::Path>(&rightVariant);
//            // TODO: implement
//            throw std::runtime_error("not implemented");
//        }
//        case fig::POLYGON: {
////            auto *right = std::get_if<fig::Polygon>(&rightVariant);
//            // TODO: implement
//            throw std::runtime_error("not implemented");
//            // return true if the polygon is degenerate into a overlaped line
//        }
    }
    return false;
}

double fig::getFiguresDistance(const fig::Path &path, const fig::figVariants &figV) {
    return 0;  //TODO
}

fig::Point fig::Path::getNearestPoint(const fig::figVariants &fig) const {
    return {}; //TODO
}
