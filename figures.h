#pragma once // NOLINT

#include <utility>
#include <vector>

class Point;
class Figure;
class Line;
class PolyLine;
class Circle;

class Point
{
public:
    Point(double x, double y): x_(x), y_(y) {}
    Point() = default;
    double x() const { return x_; }
    double y() const { return y_; }
    void x(double new_x) { x_ = new_x; }
    void y(double new_y) { y_ = new_y; }

private:
    double x_, y_;

};

class Figure // NOLINT
{
public:
    virtual double length() const = 0;
    virtual std::vector<Point> intersect(const Figure &other) const = 0;
    virtual std::vector<Point> intersect(const Line &other) const = 0;
    virtual std::vector<Point> intersect(const PolyLine &other) const = 0;
    virtual std::vector<Point> intersect(const Circle &other) const = 0;
    virtual ~Figure() = default;

};

class Line : public Figure
{
public:
    explicit Line(std::vector<Point> a): points_(std::move(a)) {}
    double length() const override;
    std::vector<Point> points() const { return points_; }
    std::vector<Point> intersect(const Figure &other) const override;
    std::vector<Point> intersect(const Line &other) const override;
    std::vector<Point> intersect(const PolyLine &other) const override;
    std::vector<Point> intersect(const Circle &other) const override;

private:
    std::vector<Point> points_;

};

class PolyLine : public Line
{
public:
    explicit PolyLine(std::vector<Point> a): Line(std::move(a)) {}
    double length() const override;
    Line get_line(int i) const;
    std::vector<Point> intersect(const Figure &other) const override;
    std::vector<Point> intersect(const Line &other) const override;
    std::vector<Point> intersect(const PolyLine &other) const override;
    std::vector<Point> intersect(const Circle &other) const override;
    std::vector<Point> intersect_helper(const Figure &other) const;
};

class Circle : public Figure
{
public:
    Circle(double x, double y, double r): x_(x), y_(y), r_(r) {}
    double x() const { return x_; }
    double y() const { return y_; }
    double r() const { return r_; }
    double length() const override;
    std::vector<Point> intersect(const Figure &other) const override;
    std::vector<Point> intersect(const Line &other) const override;
    std::vector<Point> intersect(const PolyLine &other) const override;
    std::vector<Point> intersect(const Circle &other) const override;

private:
    double x_, y_, r_;

};
