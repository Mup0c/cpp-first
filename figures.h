#pragma once
#include <vector>

using std::vector;

class Line;
class PolyLine;
class Circle;

class Point
{
public:
    Point(float x, float y): x_(x), y_(y) {}
    bool operator==(const Point &other) const;
    float distance(const Point &other) const;
    float x() const { return x_; }
    float y() const { return y_; }

private:
    double x_, y_;
};

class Figure
{
public:
    virtual ~Figure() = default;
    virtual double length() const = 0;
    virtual vector<Point> intersect(const Figure &other) const = 0;
    virtual vector<Point> intersect(const Segment &other) const = 0;
    virtual vector<Point> intersect(const Circle &other) const = 0;
    virtual vector<Point> intersect(const Polyline &other) const = 0;
};

class Line : public Figure
{
public:
    Line(pair<float, float> first, pair<float, float> second) : Figure(), first(first), second(second){}

    float length()
    {
        return GetPointsDist(first, second);
    }

private:
    pair<float, float> first, second;

};

class Circle : public Figure
{
public:
    Circle(pair<float, float> center, float radius) : Figure(), center(center), radius(radius)
    {
        cout << "Called Circle constructor" << "\n";
    }

private:
    pair<float, float> center;
    float radius;

};

class Polyline : public Figure
{
public:
    Polyline(vector<pair<float, float>> points) : Figure(), points(points)
    {
        cout << "Called Polyline constructor" << "\n";
    }

private:
    vector<int> points;

};