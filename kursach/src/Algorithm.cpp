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
        case fig::LINE:
            return doesOverlap(std::get<fig::Line>(left), right);
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
                case fig::LINE: {
                    auto line = std::get<fig::Line>(figure);

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

void Algorithm::setGcodeFilePath(const std::string &path) {
    gcode.setPath(path);
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
        case fig::LINE:
            return getFiguresDistance(std::get<fig::Line>(figV1), figV2);
        case fig::RECT:
            return getFiguresDistance(std::get<fig::Rect>(figV1), figV2);
        case fig::POLYGON:
            return getFiguresDistance(std::get<fig::Polygon>(figV1), figV2);
        case fig::PATH:
            return getFiguresDistance(std::get<fig::Path>(figV1), figV2);
    }
}


void Algorithm::setFiguresDrawingOrder() {
    double weights[svg.getFiguresCount()][svg.getFiguresCount()];

    int i = 0, j = 0;
    for (auto fig1 = svg.begin(); fig1 != svg.end(); ++fig1, ++i)
        for (auto fig2 = svg.begin(); fig2 != svg.end(); ++fig2, ++j)
            weights[i][j] = getFiguresDistance(*fig1, *fig2);


}


void Algorithm::sliceFigures() {
    for (auto figVariant = svg.begin(); figVariant != svg.end(); ++figVariant) {
        switch (figVariant->index()) {
            case fig::CIRCLE:

            case fig::LINE:

            case fig::RECT:

            case fig::POLYGON:

            case fig::PATH:

                break;
        }

    }

}

