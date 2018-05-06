#define EPS 0.000000001
#include "figures.h"
#include <cmath>


double Line::length() const
{
    return sqrt(pow(points()[1].x() - points()[0].x(), 2) + pow(points()[1].y() - points()[0].y(), 2));
}

std::vector<Point> Line::intersect(const Line &other) const
{
    std::vector<Point> result;

    double x1, y1, x2, y2, x3, y3, x4, y4;
    x1 = this->points()[0].x();
    y1 = this->points()[0].y();
    x2 = this->points()[1].x();
    y2 = this->points()[1].y();
    x3 = other.points()[0].x();
    y3 = other.points()[0].y();
    x4 = other.points()[1].x();
    y4 = other.points()[1].y();

    double d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    double u_a = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    double u_b = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    if (u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1) {
        double ans_x = x1 + u_a * (x2 - x1);
        double ans_y = y1 + u_a * (y2 - y1);
        result.emplace_back(ans_x, ans_y);
    }
    return result;
}

std::vector<Point> Line::intersect(const PolyLine &other) const
{
    return other.intersect(*this);
}

std::vector<Point> Line::intersect(const Circle &other) const
{
    std::vector<Point> result;

    Point a = this->points()[0];
    Point b = this->points()[1];
    Point o = Point(other.x(), other.y());
    double r = other.r();

    a.x(a.x() - o.x());
    a.y(a.y() - o.y());
    b.x(b.x() - o.x());
    b.y(b.y() - o.y());

    double A = a.y() - b.y();
    double B = b.x() - a.x();
    double C = a.x() * b.y() - b.x() * a.y();

    Point q = Point(0, 0);
    q.x(q.x() - (A * C) / (A * A + B * B));
    q.y(q.y() - (B * C) / (A * A + B * B));
    if (C * C <= r * r * (A * A + B * B) + EPS) {
        if (abs(C * C - r * r * (A * A + B * B)) < EPS) {
            q.x(q.x() + o.x());
            q.y(q.y() + o.y());
            result.push_back(q);
        }
        else {
            double d = r * r - C * C / (A * A + B * B);
            double mult = sqrt(d / (A * A + B * B));
            result.emplace_back(q.x() + B * mult + o.x(), q.y() - A * mult + o.y());
            result.emplace_back(q.x() - B * mult + o.x(), q.y() + B * mult + o.y());
        }
    }
    return result;
}

std::vector<Point> Line::intersect(const Figure &other) const {
    return other.intersect(*this);
}

double PolyLine::length() const
{
    double l = 0;
    for (int i = 1; i < points().size(); i++) {
        l += sqrt(pow(points()[i].x() - points()[i - 1].x(), 2) + pow(points()[i].y() + points()[i - 1].y(), 2));
    }
    return l;
}

Line PolyLine::get_line(int i) const
{
    std::vector<Point> a;
    a.emplace_back(points()[i - 1].x(), points()[i - 1].y());
    a.emplace_back(points()[i].x(), points()[i].y());
    return Line(a);
}

std::vector<Point> PolyLine::intersect(const Figure &other) const {
    return this->intersect_helper(other);
}

std::vector<Point> PolyLine::intersect(const Line &other) const {
    return this->intersect_helper(other);
}

std::vector<Point> PolyLine::intersect(const PolyLine &other) const {
    return this->intersect_helper(other);
}

std::vector<Point> PolyLine::intersect(const Circle &other) const {
    return this->intersect_helper(other);
}

std::vector<Point> PolyLine::intersect_helper(const Figure &other) const {
    std::vector<Point> result;
    for (int i = 1; i < this->points().size(); i++) {
        std::vector<Point> r = this->get_line(i).intersect(other);
        for (auto j : r) {
            result.push_back(j);
        }
    }
    return result;
}

double Circle::length() const {
    return 2 * M_PI * r();
}

std::vector<Point> Circle::intersect(const Line &other) const {
    return other.intersect(*this);
}

std::vector<Point> Circle::intersect(const PolyLine &other) const {
    return other.intersect(*this);
}

std::vector<Point> Circle::intersect(const Circle &other) const {
    std::vector<Point> result;

    double d = sqrt(pow(other.x() - this->x(), 2) + pow(other.y() - this->y(), 2));
    bool nesting = abs(other.r() - this->r()) > d;
    bool no_intersection = d > other.r() + this->r();
    if (!(nesting || no_intersection)) {
        double b = (pow(this->r(), 2) - pow(other.r(), 2) + pow(d, 2)) / (2 * d);
        double a = d - b;
        Point p0 = Point(0, 0);
        p0.x(other.x() + a / d * (this->x() - other.x()));
        p0.y(other.y() + a / d * (this->y() - other.y()));
        if (d == other.r() + this->r()) {
            result.push_back(p0);
        } else {
            double h = sqrt(pow(other.r(), 2) - pow(a, 2));
            Point p3 = Point(0, 0), p4 = Point(0, 0);
            p3.x(p0.x() + (this->y() - other.y()) * h / d);
            p3.y(p0.y() - (this->x() - other.x()) * h / d);
            p4.x(p0.x() - (this->y() - other.y()) * h / d);
            p4.y(p0.y() + (this->x() - other.x()) * h / d);
            result.push_back(p3);
            result.push_back(p4);
        }
    }
    return result;
}

std::vector<Point> Circle::intersect(const Figure &other) const {
    return other.intersect(*this);
}