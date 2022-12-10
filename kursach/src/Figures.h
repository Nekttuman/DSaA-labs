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

namespace fig {

    struct Point;

    class Circle;

    class Rect;

    class Line;

    class Polygon;

    class Path;


    typedef std::variant<fig::Circle, fig::Line, fig::Rect, fig::Polygon, fig::Path> figVariants;


    int getNumberFromRegex(const std::regex &reg, const std::string &svgStr);

    double getDistance(Point a, Point b);


    enum FigureType {
        CIRCLE,
        LINE,
        RECT,
        POLYGON,
        PATH,
    };


    struct Point {
        int x = 0, y = 0;

        bool operator==(const Point &other) const;

        bool operator!=(const Point &other) const;
    };


////////////////////////////////////// PRIMITIVES /////////////////////////////////////////////////

    class Figure {
    public:
        virtual void parseSvg(const std::string &) = 0;

        virtual void print() const = 0;
    };


    class Circle : public Figure {
        Point m_c;
        int m_r = 0;
    public:
        Circle() = default;

        Circle(int cx, int cy, int r) : m_c{cx, cy}, m_r(r) {}

        Point getCenter() const { return m_c; }

        int getRadius() const { return m_r; }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;

        bool isPointBelongs(const fig::Point &p) const {
            return pow(p.x - m_c.x, 2) + pow(p.y - m_c.y, 2) <= pow(m_r, 2);
        }

        friend bool operator==(const Circle &left, const Circle &right);

        friend bool isOverlaps(const Circle &left, fig::figVariants rightVariant);
    };


    class Rect : public Figure {
        int m_width = 0, m_height = 0;
        Point m_coord;
    public:
        Rect() = default;

        Rect(int w, int h, int x, int y) : m_height(h), m_width(w), m_coord{x, y} {}

        Point getPosition() const { return m_coord; }

        int getWidth() const { return m_width; }

        int getHeight() const { return m_height; }


        void parseSvg(const std::string &svgStr) override;

        void print() const override;


        friend bool operator==(const Rect &left, const Rect &right);

        friend bool isOverlaps(const Rect &left, const figVariants &right);
    };


//////////////////////////////// POINT-BASED FIGURES //////////////////////////////////////////////

    class Line : public Figure {
        Point one, two;
    public:
        Line() = default;

        Line(int x1, int y1, int x2, int y2) :
                one{x1, y1}, two{x2, y2} {}

        Point getPoint1() const { return one; }

        Point getPoint2() const { return two; }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;


        friend bool operator==(const Line &left, const Line &right);

        friend bool isOverlaps(const Line &left, const figVariants &right);
    };


    class Polygon : public Figure {
        // <polygon points="0,100 50,25 50,75 100,0" />
        std::vector<Point> m_points;
    public:
        Polygon() = default;

        explicit Polygon(const std::vector<Point> &points) { m_points = points; }

        void parseSvg(const std::string &svgStr) override;

        void print() const override;

        auto begin() { return std::begin(m_points); }

        auto end() { return std::end(m_points); }

        friend bool operator!=(const Polygon &left, const Polygon &right);

        friend bool operator==(const fig::Polygon &left, const fig::Polygon &right);

        friend bool isOverlaps(const Polygon &left, const figVariants &right);
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

        auto begin() { return std::begin(m_points); }

        auto end() { return std::end(m_points); }

        friend bool operator==(const Path &left, const Path &right);

        friend bool isOverlaps(const Path &left, const figVariants &right);
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
