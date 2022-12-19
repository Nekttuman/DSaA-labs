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
        case fig::SEGMENT:
            return doesOverlap(std::get<fig::Segment>(left), right);
        case fig::RECT:
            return doesOverlap(std::get<fig::Rect>(left), right);
        case fig::POLYGON:
            return doesOverlap(std::get<fig::Polygon>(left), right);
        case fig::PATH:
            return doesOverlap(std::get<fig::Path>(left), right);
    }
    return 0;
}

bool doesIntersect(const fig::figVariants &left, const fig::figVariants &right) {
    return false; //TODO: implement alg intersect detecting
}


fig::figVariants intersect(const fig::figVariants &left, const fig::figVariants &right) {
    return fig::Circle(0, 0, 10); //TODO: implement alg intersect
}

//////////////////////////////////////// METHODS ////////////////////////////////////////////////


void Algorithm::parseSvg(const std::string &path) {
    svg.empty();
    svg.parse(path);
}

void Algorithm::logSvg() {
    std::cout << svg;
}

#include <SFML/Graphics.hpp>

int Algorithm::drawParsed() {
    sf::RenderWindow App(sf::VideoMode(svg.getWidth(), svg.getHeight()), "svg", sf::Style::Close);
    sf::Event Event;
    while (true) {
        App.clear(sf::Color::White);
        //Verifying events
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                return (-1);
            }
        }

        for (auto figure: svg) {
            switch (figure.index()) {
                case fig::CIRCLE: {
                    auto circle = std::get<fig::Circle>(figure);

                    int r = circle.getRadius();
                    sf::CircleShape sfmlCircle(r);
                    sfmlCircle.setPosition(circle.getCenter().x - r, circle.getCenter().y - r);
                    sfmlCircle.setFillColor(sf::Color::Black);

                    App.draw(sfmlCircle);
                    break;
                }
                case fig::RECT: {
                    auto rect = std::get<fig::Rect>(figure);

                    sf::RectangleShape sfmlRect({rect.getWidth(), rect.getHeight()});
                    sfmlRect.setPosition(rect.getPosition().x, rect.getPosition().y);
                    sfmlRect.setFillColor(sf::Color::Black);

                    App.draw(sfmlRect);
                    break;
                }
                case fig::SEGMENT: {
                    auto line = std::get<fig::Segment>(figure);

                    sf::Vertex sfmlLine[] = {
                            sf::Vertex({line.getPoint1().x, line.getPoint1().y}, sf::Color::Black),
                            sf::Vertex({line.getPoint2().x, line.getPoint2().y}, sf::Color::Black)
                    };

                    App.draw(sfmlLine, 2, sf::Lines);
                    break;
                }
                case fig::POLYGON: {
                    auto poly = std::get<fig::Polygon>(figure);

                    sf::ConvexShape convex;
                    convex.setPointCount(poly.getPointsCount());
                    int index = 0;
                    for (auto point: poly)
                        convex.setPoint(index++, {point.x, point.y});
                    convex.setFillColor(sf::Color::Black);

                    App.draw(convex);
                    break;
                }
                case fig::PATH: {
                    auto path = std::get<fig::Path>(figure);

                    sf::ConvexShape convex;
                    convex.setPointCount(path.getPointsCount());
                    int index = 0;
                    for (auto point: path)
                        convex.setPoint(index++, {point.x, point.y});
                    convex.setOutlineThickness(1);
                    convex.setOutlineColor(sf::Color::Black);

                    App.draw(convex);
                    break;
                }
            }
        }
        App.display();
    }
}


void Algorithm::mergeIntersectFigures() {
    if (svg.getFiguresCount() < 2) return;
    fig::figVariants newFig;
    auto end = svg.end();
    for (auto first = svg.begin(); first != end - 1; ++first)
        for (auto second = svg.begin() + 1; second != end; ++second) {
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


double getFiguresDistance(fig::figVariants figV1, fig::figVariants figV2) {
    switch (figV1.index()) {
        case fig::CIRCLE:
            return getFiguresDistance(std::get<fig::Circle>(figV1), figV2);
        case fig::SEGMENT:
            return getFiguresDistance(std::get<fig::Segment>(figV1), figV2);
        case fig::RECT:
            return getFiguresDistance(std::get<fig::Rect>(figV1), figV2);
        case fig::POLYGON:
            return getFiguresDistance(std::get<fig::Polygon>(figV1), figV2);
        case fig::PATH:
            return getFiguresDistance(std::get<fig::Path>(figV1), figV2);
    }
}


#include <cfloat>

void Algorithm::setFiguresDrawingOrder() {
    unsigned nodesCount = svg.getFiguresCount();
    double weights[nodesCount][nodesCount];

    int row = 0, col = 0;
    for (auto fig1 = svg.begin(); fig1 != svg.end(); ++fig1, ++row) {
        for (auto fig2 = svg.begin(); fig2 != svg.end(); ++fig2, ++col)
            weights[row][col] = getFiguresDistance(*fig1, *fig2);
        col = 0;
    }

    double resultPathLen = DBL_MAX;

    std::vector<int> path;
    std::vector<bool> mask;
    mask.reserve(nodesCount);
    for (int i = 0; i < nodesCount; ++i) {
        mask.push_back(false);
        path.push_back(0);
    }
    double pathWeight = 0;
    int pathIter;

    for (int firstNum = 0; firstNum < nodesCount; ++firstNum) {
        for (int i = 0; i < nodesCount; ++i) {
            mask[i] = false;
            path[i] = 0;
        }
        pathWeight = 0;
        path[0] = firstNum;
        pathIter = 1;
        mask[firstNum] = true;
        bool allMarked = false;

        for (int i = path[0]; !allMarked;) {
            auto min = DBL_MAX;
            for (int j = 0; j < nodesCount; ++j) {
                if (min > weights[i][j] && weights[i][j] != 0 && !mask[j]) {
                    min = weights[i][j];
                    path[pathIter] = j;
                }
            }
            mask[path[pathIter]] = true;
            pathWeight += weights[i][path[pathIter]];
            i = path[pathIter];
            pathIter++;

            allMarked = mask[0];
            for (auto m: mask)
                allMarked = m && allMarked;
        }


        if (pathWeight < resultPathLen) {
            resultPathLen = pathWeight;
            m_figDrawingOrder = path;
        }
    }
}


void Algorithm::sliceFigures() {
    for (auto order = m_figDrawingOrder.begin(); order != m_figDrawingOrder.end(); ++order) {
        switch (svg.get(*order).index()) {
            case fig::CIRCLE: {
                fig::Circle c = std::get<fig::Circle>(svg.get(*order));
                sliceCircle(c, m_figSlicePoints[*order].second);
                break;
            }
            case fig::SEGMENT: {
                fig::Segment s = std::get<fig::Segment>(svg.get(*order));
                auto startP = m_figSlicePoints[*order].first,
                        endP = m_figSlicePoints[*order].second;
                if (startP != endP)
                    sliceSegment(s, startP, endP);
                else {
                    fig::Point diffP = (s.getPoint1() == startP ? s.getPoint2() : s.getPoint1());
                    sliceSegment(s, startP, diffP);
                }
                break;
            }
            case fig::RECT: {

                fig::Rect rect = std::get<fig::Rect>(svg.get(*order));
                sliceRect(rect, m_figSlicePoints[*order].second);
                break;
            }

            case fig::POLYGON:

            case fig::PATH:

                break;
        }

    }

}

void Algorithm::sliceCircle(const fig::Circle &circle, const fig::Point &startP) {
    std::list<fig::Point> points;

    fig::slicedFig slicedCircle{fig::CIRCLE, startP, startP, {}};

    const int pointsCount = 100;

    fig::Point center = circle.getCenter();
    double radius = circle.getRadius();
    double dx = radius * 2 / pointsCount;

    double xs = center.x - radius;
    double x = xs, y1, y2;
    slicedCircle.points.push_back({xs, center.y});
    for (int i = 0; i < pointsCount; ++i) {
        x = x + dx;
        y1 = sqrt(std::abs(radius * radius - (x - center.x) * (x - center.x))) + center.y;
        y2 = -sqrt(std::abs(radius * radius - (x - center.x) * (x - center.x))) + center.y;
        slicedCircle.points.push_front({x, y1});
        slicedCircle.points.push_back({x, y2});
    }

    m_slicedFigures.push_back(slicedCircle);
}


void Algorithm::sliceSegment(const fig::Segment &seg, const fig::Point &startP, const fig::Point &endP) {
    m_slicedFigures.push_back(fig::slicedFig{fig::SEGMENT, startP, endP, {startP, endP}});
}


fig::Point getNearestPoint(const fig::figVariants &curFig, const fig::figVariants &nextFig) {
    switch (curFig.index()) {
        case fig::CIRCLE:
            return std::get<fig::Circle>(curFig).getNearestPoint(nextFig);
        case fig::SEGMENT:
            return std::get<fig::Segment>(curFig).getNearestPoint(nextFig);
        case fig::RECT:
            return std::get<fig::Rect>(curFig).getNearestPoint(nextFig);
        case fig::POLYGON:
            return std::get<fig::Polygon>(curFig).getNearestPoint(nextFig);
        case fig::PATH:
            return std::get<fig::Path>(curFig).getNearestPoint(nextFig);
            break;
    }
    return {0, 0};
}


#include <algorithm>

fig::Point getAnyPointDifferentTo(const fig::figVariants &figV, const fig::Point &diff) {
    switch (figV.index()) {
        case fig::CIRCLE: {
            fig::Circle c = std::get<fig::Circle>(figV);
            fig::Point p{c.getCenter().x - c.getRadius(), c.getCenter().y};
            if (p == diff)
                return {c.getCenter().x, c.getCenter().y - c.getRadius()};
            return p;
        }
        case fig::SEGMENT: {
            fig::Segment s = std::get<fig::Segment>(figV);
            if (s.getPoint1() == diff)
                return s.getPoint2();
            return s.getPoint1();
        }
        case fig::RECT:{
            fig::Rect r = std::get<fig::Rect>(figV);
            if (r.getPosition() == diff)
                return {r.getPosition().x, r.getPosition().y+r.getHeight()};
            return r.getPosition();
        }
        case fig::POLYGON:
        case fig::PATH:
            return {};
    }
}

void Algorithm::setFiguresSlicePoints() {
    for (int i = 0; i < svg.getFiguresCount(); ++i)
        m_figSlicePoints.push_back({{0, 0},
                                    {0, 0}});


    auto order = m_figDrawingOrder.begin();

    if (svg.getFiguresCount() == 1) {
        auto fig = svg.get(*order);
        m_figSlicePoints[0] = {getAnyPointDifferentTo(fig, {}), getAnyPointDifferentTo(fig, {})};
        return;
    }


    if (svg.getFiguresCount() == 2) {
        auto firstFig = svg.get(*order);
        auto secondFig = svg.get(*(order + 1));

        fig::Point endP1 = getNearestPoint(firstFig, secondFig),
                startP2 = getNearestPoint(secondFig, firstFig);
        m_figSlicePoints[*order] = {getAnyPointDifferentTo(firstFig, endP1), endP1};
        m_figSlicePoints[*(order + 1)] = {startP2, getAnyPointDifferentTo(secondFig, startP2)};
        return;
    }

// 3 or more figures

    fig::figVariants prevFig;
    auto curFig = svg.get(*order);
    auto nextFig = svg.get(*(order + 1));

    //start figure
    fig::Point startP, endP = getNearestPoint(curFig, nextFig);
    m_figSlicePoints[*order] = {getAnyPointDifferentTo(curFig, endP), endP};
    ++order;

    for (; order != m_figDrawingOrder.end() - 1; ++order) {
        prevFig = curFig;
        curFig = nextFig;
        nextFig = svg.get(*(order + 1));

        startP = getNearestPoint(curFig, prevFig);
        endP = getNearestPoint(curFig, nextFig);
        m_figSlicePoints[*order] = {startP, endP};
    }

    //for last figure
    startP = getNearestPoint(nextFig, curFig);
    m_figSlicePoints[*order] = {startP, getAnyPointDifferentTo(nextFig, startP)};


}

int Algorithm::drawPath() {
    sf::RenderWindow App(sf::VideoMode(svg.getWidth(), svg.getHeight()), "svg", sf::Style::Close);
    sf::Event Event;
    while (true) {
        App.clear(sf::Color::White);
        //Verifying events
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                return (-1);
            }
        }

        for (auto figure: svg) {
            switch (figure.index()) {
                case fig::CIRCLE: {
                    auto circle = std::get<fig::Circle>(figure);

                    int r = circle.getRadius();
                    sf::CircleShape sfmlCircle(r);
                    sfmlCircle.setPosition(circle.getCenter().x - r, circle.getCenter().y - r);
                    sfmlCircle.setFillColor(sf::Color::Black);

                    App.draw(sfmlCircle);
                    break;
                }
                case fig::RECT: {
                    auto rect = std::get<fig::Rect>(figure);

                    sf::RectangleShape sfmlRect({rect.getWidth(), rect.getHeight()});
                    sfmlRect.setPosition(rect.getPosition().x, rect.getPosition().y);
                    sfmlRect.setFillColor(sf::Color::Black);

                    App.draw(sfmlRect);
                    break;
                }
                case fig::SEGMENT: {
                    auto line = std::get<fig::Segment>(figure);

                    sf::Vertex sfmlLine[] = {
                            sf::Vertex({line.getPoint1().x, line.getPoint1().y}, sf::Color::Black),
                            sf::Vertex({line.getPoint2().x, line.getPoint2().y}, sf::Color::Black)
                    };

                    App.draw(sfmlLine, 2, sf::Lines);
                    break;
                }
                case fig::POLYGON: {
                    auto poly = std::get<fig::Polygon>(figure);

                    sf::ConvexShape convex;
                    convex.setPointCount(poly.getPointsCount());
                    int index = 0;
                    for (auto point: poly)
                        convex.setPoint(index++, {point.x, point.y});
                    convex.setFillColor(sf::Color::Black);

                    App.draw(convex);
                    break;
                }
                case fig::PATH: {
                    auto path = std::get<fig::Path>(figure);

                    sf::ConvexShape convex;
                    convex.setPointCount(path.getPointsCount());
                    int index = 0;
                    for (auto point: path)
                        convex.setPoint(index++, {point.x, point.y});
                    convex.setOutlineThickness(1);
                    convex.setOutlineColor(sf::Color::Black);

                    App.draw(convex);
                    break;
                }
            }
        }

        if (svg.getFiguresCount() > 1)
            for (auto iter = m_figDrawingOrder.begin(); iter != m_figDrawingOrder.end() - 1; ++iter) {
                fig::Point p1 = m_figSlicePoints[*iter].second;
                fig::Point p2 = m_figSlicePoints[*(iter + 1)].first;

                sf::Vertex sfmlLine[] = {
                        sf::Vertex(sf::Vector2f(p1.x, p1.y), sf::Color::Red),
                        sf::Vertex(sf::Vector2f(p2.x, p2.y), sf::Color::Red)
                };

                App.draw(sfmlLine, 2, sf::Lines);
            }

        App.display();
    }

    return 0;
}


void Algorithm::sliceRect(const fig::Rect &rect, const fig::Point &startP) {
    std::list<fig::Point> points;

    fig::Point pos = rect.getPosition();
    double h = rect.getHeight(), w = rect.getWidth();

    if (startP == pos)
        points = {pos, {pos.x+w, pos.y}, {pos.x+w, pos.y+h}, {pos.x, pos.y+h}, pos};
    else if (startP == fig::Point{pos.x+w, pos.y})
        points = {{pos.x+w, pos.y}, {pos.x+w, pos.y+h}, {pos.x, pos.y+h}, pos, {pos.x+w, pos.y}};
    else if (startP == fig::Point{pos.x+w, pos.y+h})
        points = {{pos.x+w, pos.y+h}, {pos.x, pos.y+h}, pos, {pos.x+w, pos.y}, {pos.x+w, pos.y+h}};
    else
        points = {{pos.x, pos.y+h}, pos, {pos.x+w, pos.y}, {pos.x+w, pos.y+h}, {pos.x, pos.y+h}};


    m_slicedFigures.push_back(fig::slicedFig{fig::RECT, startP, startP, points});
}


