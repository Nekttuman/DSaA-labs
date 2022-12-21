//
// Created by nektt on 27/11/2022.
//

#ifndef KURSACH2_FIGURES_H
#define KURSACH2_FIGURES_H

#include <fstream>
#include <vector>
#include <regex>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <variant>
#include <numeric>
#include <list>

namespace fig {

    struct Point;

    class Circle;

    class Rect;

    class Segment;

    class Polygon;

    class Path;


    typedef std::variant<fig::Circle, fig::Segment, fig::Rect, fig::Polygon, fig::Path> figVariants;


    int getNumberFromRegex(const std::regex &reg, const std::string &svgStr);

    double getDistance(Point a, Point b);

    double getDistance(const Segment &line, fig::Point point);

    enum FigureType {
        CIRCLE,
        SEGMENT,
        RECT,
        POLYGON,
        PATH,
    };


    struct Point {
        double x = 0, y = 0;

        bool operator==(const Point &other) const;

        bool operator!=(const Point &other) const;
    };


////////////////////////////////////// PRIMITIVES /////////////////////////////////////////////////

    class Figure {
    public:
        virtual void parseSvg(const std::string &) = 0;

        virtual void print() const = 0;
    };


    struct slicedFig{
        fig::FigureType ft;
        fig::Point startP, endP;
        std::list<fig::Point> points;
    };



    class Circle : public Figure {
        Point m_c;
        int m_r = 0;
    public:
        Circle() = default;

        Circle(double cx, double cy, int r) : m_c{cx, cy}, m_r(r) {}

        Point getCenter() const { return m_c; }

        int getRadius() const { return m_r; }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;

        fig::Point getNearestPoint(const fig::figVariants &figVariant) const;

        bool pointBelongs(const fig::Point &p) const {
            return pow(p.x - m_c.x, 2) + pow(p.y - m_c.y, 2) <= pow(m_r, 2);
        }

        friend bool operator==(const Circle &left, const Circle &right);

        friend bool doesOverlap(const Circle &left, fig::figVariants rightVariant);

        friend double getFiguresDistance(const fig::Circle &circle, const figVariants &figV);
    };


    class Rect : public Figure {
        int m_width = 0, m_height = 0;
        Point m_coord;
    public:
        Rect() = default;

        Rect(int w, int h, double x, double y) : m_height(h), m_width(w), m_coord{x, y} {}

        Point getPosition() const { return m_coord; }

        int getWidth() const { return m_width; }

        int getHeight() const { return m_height; }

        bool pointBelongs(const fig::Point &p) const {
            return p.x <= m_coord.x + m_width && p.x >= m_coord.x &&
                   p.y <= m_coord.y + m_height && p.y >= m_coord.y;
        }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;

        fig::Point getNearestPoint(const fig::figVariants &figV) const;


        friend bool operator==(const Rect &left, const Rect &right);

        friend bool doesOverlap(const Rect &left, figVariants rightVariant);

        friend double getFiguresDistance(const fig::Rect &lRect, const figVariants &figV);
    };


//////////////////////////////// POINT-BASED FIGURES //////////////////////////////////////////////



    class Segment : public Figure {
        Point one, two;
    public:
        Segment() = default;

        Segment(double x1, double y1, double x2, double y2) :
                one{x1, y1}, two{x2, y2} {}

        Segment(fig::Point p1, fig::Point p2) :
                one{p1}, two{p2} {}

        Point getPoint1() const { return one; }

        Point getPoint2() const { return two; }

        void parseSvg(const std::string &svgStr) override;

        bool pointBelongs(const fig::Point &p) const {
            double minx = (one.x > two.x) ? two.x : one.x;
            double maxx = (one.x < two.x) ? two.x : one.x;
            double miny = (one.y > two.y) ? two.y : one.y;
            double maxy = (one.y < two.y) ? two.y : one.y;
            bool belongsLine =  (p.y - one.y) * (two.x - one.x) - (two.y - one.y) * (p.x - one.x) <= std::numeric_limits<double>::epsilon();

            return belongsLine &&
                   p.x >= minx && p.x <= maxx && p.y >= miny && p.y <= maxy;;
        }

        void print() const override;

        fig::Point getNearestPoint(const fig::figVariants &figV) const;

        friend bool doesOverlap(const Segment &left, figVariants rightVariant);

        friend bool operator==(const Segment &left, const Segment &right);

        friend double getFiguresDistance(const fig::Segment &seg, const figVariants &figV);

    };


    class Polygon : public Figure {
        // <polygon points="0,100 50,25 50,75 100,0" />
        std::vector<Point> m_points;
    public:
        Polygon() = default;

        explicit Polygon(const std::vector<Point> &points) { m_points = points; }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;

        fig::Point getNearestPoint(const fig::figVariants &fig) const;

        unsigned getPointsCount() { return m_points.size(); }

        const auto begin() const { return std::begin(m_points); }

        auto begin() { return std::begin(m_points); }

        const auto end() const { return std::end(m_points); }

        auto end() { return std::end(m_points); }

        friend bool operator!=(const Polygon &left, const Polygon &right);

        friend bool operator==(const fig::Polygon &left, const fig::Polygon &right);

        friend bool doesOverlap(const Polygon &left, const figVariants &right);

        friend double getFiguresDistance(const fig::Polygon &polygon, const figVariants &figV);
    };


    class Path : public Figure {
        std::vector<Point> m_points;
        bool m_fromPolygon;
    public:
        explicit Path(bool fromPolygon = false) :
                m_fromPolygon(fromPolygon) {};

        explicit Path(const std::vector<Point> &points) { m_points = points; }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;

        fig::Point getNearestPoint(const fig::figVariants &fig) const;

        unsigned getPointsCount() { return m_points.size(); }

        const auto begin() const { return std::begin(m_points); }

        auto begin() { return std::begin(m_points); }

        const auto end() const { return std::end(m_points); }

        auto end() { return std::end(m_points); }

        friend bool operator==(const Path &left, const Path &right);

        friend bool doesOverlap(const Path &left, const figVariants &rightVariant);

        friend double getFiguresDistance(const fig::Path &path, const figVariants &figV);
    };


// TODO: parse <path/> tag
//    <path
//            fill="none" / smth -> (0/1)
//            stroke="red" / ignore
//          d="M 10,30               A d is a list of path commands
//            A 20,20 0,0,1 50,30       commands description look at
//            A 20,20 0,0,1 90,30       https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/d#path_commands
//            Q 90,60 50,90
//            Q 10,60 10,30 z" />
//

};


std::ostream &operator<<(std::ostream &out, const fig::Point &point);


#endif //KURSACH2_FIGURES_H
