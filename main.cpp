#include "catch.hpp"
#include "figures.h"

#define EPS 0.00000001

//done: не сравинтваь даблы, вынести метод интерсект полилайна в интерсект с фигурой, тест с длиной добавить делит указателей(память)


TEST_CASE("length") {
    std::vector<std::shared_ptr<Figure>> v(3);
    std::vector<Point> points(2);
    points[0].x(0.0);
    points[0].y(2.0);
    points[1].x(4.0);
    points[1].y(6.0);
    v[0] = std::make_shared<Line>(points);

    points.resize(3);
    points[0].x(0.0);
    points[0].y(0.0);
    points[1].x(-3.0);
    points[1].y(4.0);
    points[2].x(-7.0);
    points[2].y(7.0);
    v[1] = std::make_shared<PolyLine>(points);

    v[2] = std::make_shared<Circle>(4.0, -9.0, 8.0);

    CHECK(abs(v[0]->length() - 5.65685424949238) < EPS);
    CHECK(abs(v[1]->length() - 16.7046999107) < EPS);
    CHECK(abs(v[2]->length() - 2*25.132741228718346) < EPS);
}

TEST_CASE("Contain objects of different classes in one vector") {
    std::vector<std::shared_ptr<Figure>> v(3);
    std::vector<Point> points(3);
    points[1].x(0.0);
    points[1].y(2.0);
    points[2].x(4.0);
    points[2].y(6.0);
    v[0] = std::make_shared<Line>(points);

    points.resize(3);
    points[0].x(5.0);
    points[0].y(3.0);
    points[1].x(-6.0);
    points[1].y(8.0);
    points[2].x(11.0);
    points[2].y(-7.0);
    v[1] = std::make_shared<PolyLine>(points);

    v[2] = std::make_shared<Circle>(4.0, -9.0, 8.0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::vector<Point> result = v[i]->intersect(*v[j]);
        }
    }
}

TEST_CASE("intersect line with line") {
    SECTION("Simple intersection") { // NOLINT
        std::vector<Point> e, f;
        e.emplace_back(0.0, 0.0);
        e.emplace_back(4.0, 4.0);
        f.emplace_back(2.0, 0.0);
        f.emplace_back(2.0, 4.0);

        Line line1 = Line(e);
        Line line2 = Line(f);

        Point expected_point(2.0, 2.0);
        std::vector<Point> result = line1.intersect(line2);

        CHECK(abs(result[0].x() - expected_point.x()) < EPS);
        CHECK(abs(result[0].y() - expected_point.y()) < EPS);
    }

    SECTION("No intersection") { // NOLINT
        Point a = Point(0.0, 0.0), b = Point(4.0, 4.0), c = Point(2.0, 3.0), d = Point(2.0, 4.0);
        std::vector<Point> e, f;
        e.emplace_back(a);
        e.emplace_back(b);
        f.emplace_back(c);
        f.emplace_back(d);

        Line line1 = Line(e);
        Line line2 = Line(f);

        std::vector<Point> result = line1.intersect(line2);

        CHECK(result.empty());
    }

    SECTION("Same point") { // NOLINT
        Point a = Point(0.0, 0.0), b = Point(4.0, 4.0), c = Point(0.0, 0.0), d = Point(0.0, 2.0);
        std::vector<Point> e, f;
        e.emplace_back(a);
        e.emplace_back(b);
        f.emplace_back(c);
        f.emplace_back(d);

        Line line1 = Line(e);
        Line line2 = Line(f);

        Point expected_point(Point(0.0, 0.0));
        std::vector<Point> result = line1.intersect(line2);

        CHECK(abs(result[0].x() - expected_point.x()) < EPS);
        CHECK(abs(result[0].y() - expected_point.y()) < EPS);
    }

    SECTION("Same lines") { // NOLINT
        Point a = Point(0.0, 0.0), b = Point(4.0, 4.0), c = Point(0.0, 0.0), d = Point(4.0, 4.0);
        std::vector<Point> e, f;
        e.emplace_back(a);
        e.emplace_back(b);
        f.emplace_back(c);
        f.emplace_back(d);

        Line line1 = Line(e);
        Line line2 = Line(f);

        std::vector<Point> result = line1.intersect(line2);

        CHECK(result.empty());
    }

    SECTION("Very close, no intersection") { // NOLINT
        Point a = Point(0.0, 0.0), b = Point(4.0, 4.0), c = Point(2.0, 0.0), d = Point(2.0, 1.9999999999999);
        std::vector<Point> e, f;
        e.emplace_back(a);
        e.emplace_back(b);
        f.emplace_back(c);
        f.emplace_back(d);

        Line line1 = Line(e);
        Line line2 = Line(f);

        std::vector<Point> result = line1.intersect(line2);

        CHECK(result.empty());
    }

}

TEST_CASE("intersect line with polyline") {
    std::vector<Point> points;
    points.emplace_back(0.0, 0.0);
    points.emplace_back(4.0, 4.0);
    points.emplace_back(Point(2.0, 0.0));
    points.emplace_back(2.0, 4.0);
    PolyLine polyline(points);

    std::vector<Point> a;
    a.emplace_back(Point(0.0, 3.0));
    a.emplace_back(Point(4.0, 3.0));
    Line line(a);

    std::vector<Point> expected_points;
    expected_points.emplace_back(Point(3.0, 3.0));
    expected_points.emplace_back(Point(3.5, 3.0));
    expected_points.emplace_back(Point(2.0, 3.0));
    std::vector<Point> result = line.intersect(polyline);
    CHECK(result.size() == expected_points.size());
    for (int i = 0; i < result.size(); i++) {
        CHECK(abs(result[i].x() - expected_points[i].x()) < EPS);
        CHECK(abs(result[i].y() - expected_points[i].y()) < EPS);
    }
}

TEST_CASE("intersect polyline with polyline") {
    std::vector<Point> points;
    points.emplace_back(Point(6.0, 4.0));
    points.emplace_back(Point(0.0, 1.0));
    points.emplace_back(Point(5.0, 1.0));
    PolyLine first_poly(points);

    points.clear();
    points.emplace_back(Point(1.0, 3.0));
    points.emplace_back(Point(4.0, 0.0));
    points.emplace_back(Point(4.0, 4.0));
    PolyLine second_poly(points);

    std::vector<Point> expected_points;
    expected_points.emplace_back(Point(2.0, 2.0));
    expected_points.emplace_back(Point(4.0, 3.0));
    expected_points.emplace_back(Point(3.0, 1.0));
    expected_points.emplace_back(Point(4.0, 1.0));

    std::vector<Point> result = first_poly.intersect(second_poly);
    CHECK(result.size() == expected_points.size());
    for (int i = 0; i < result.size(); i++) {
        CHECK(abs(result[i].x() - expected_points[i].x()) < EPS);
        CHECK(abs(result[i].y() - expected_points[i].y()) < EPS);
    }
}

TEST_CASE("intersect line with circle") {
    SECTION("In two points") { // NOLINT
        Circle circle(2.0, 2.0, 2);

        std::vector<Point> b;
        b.emplace_back(Point(1.0, 5.0));
        b.emplace_back(Point(5.0, 1.0));
        Line line(b);

        std::vector<Point> expected_points;
        expected_points.emplace_back(Point(4.0, 2.0));
        expected_points.emplace_back(Point(2.0, 4.0));

        std::vector<Point> result = line.intersect(circle);
        CHECK(result.size() == 2);
        for (int i = 0; i < result.size(); i++) {
            CHECK(abs(result[i].x() - expected_points[i].x()) < EPS);
            CHECK(abs(result[i].y() - expected_points[i].y()) < EPS);
        }
    }

    SECTION("No intersection") { // NOLINT
        Circle circle(2.0, 2.0, 2);

        std::vector<Point> b;
        b.emplace_back(Point(5.0, 5.0));
        b.emplace_back(Point(5.0, 1.0));
        Line line(b);

        std::vector<Point> result = circle.intersect(line);
        CHECK(result.empty());
    }

    SECTION("In one point") { // NOLINT
        Circle circle(2.0, 2.0, 2);

        std::vector<Point> b;
        b.emplace_back(Point(4.0, 5.0));
        b.emplace_back(Point(4.0, 1.0));
        Line line(b);

        Point expected_point(Point(4.0, 2.0));

        std::vector<Point> result = line.intersect(circle);
        CHECK(result.size() == 1);
        CHECK(abs(expected_point.x() - result[0].x()) < EPS);
        CHECK(abs(expected_point.y() - result[0].y()) < EPS);
    }
}

TEST_CASE("intersect polyline line with circle") {
    std::vector<Point> points;
    points.emplace_back(Point(2.0, 5.0));
    points.emplace_back(Point(2.0, -1.0));
    points.emplace_back(Point(4.0, -1.0));
    points.emplace_back(Point(4.0, 5.0));
    PolyLine broken_line(points);

    Circle circle(2.0, 2.0, 2.0);

    std::vector<Point> expected_points;
    expected_points.emplace_back(Point(2.0, 0.0));
    expected_points.emplace_back(Point(2.0, 2.0));
    expected_points.emplace_back(Point(4.0, 2.0));

    std::vector<Point> result = circle.intersect(broken_line);
    CHECK(result.size() == 3);
    for (int i = 0; i < result.size(); i++) {
        CHECK(abs(result[i].x() - expected_points[i].x()) < EPS);
        CHECK(abs(result[i].y() - expected_points[i].y()) < EPS);
    }
}

TEST_CASE("intersect circle with circle") {
    SECTION("intersect in two points") { // NOLINT
        Circle first_circle(0.0, 0.0, 2.0);

        Circle second_circle(2.0, 2.0, 2.0);

        std::vector<Point> expected_points;
        expected_points.emplace_back(Point(0.0, 2.0));
        expected_points.emplace_back(Point(2.0, 0.0));

        std::vector<Point> result = first_circle.intersect(second_circle);
        CHECK(result.size() == expected_points.size());
        for (int i = 0; i < result.size(); i++) {
            CHECK(abs(result[i].x() - expected_points[i].x()) < EPS);
            CHECK(abs(result[i].y() - expected_points[i].y()) < EPS);
        }
    }

    SECTION("intersect in one point") { // NOLINT
        Circle first_circle(0.0, 0.0, 3.0);

        Circle second_circle(0.0, 6.0, 3.0);

        std::vector<Point> expected_points;
        expected_points.emplace_back(Point(0.0, 3.0));

        std::vector<Point> result = first_circle.intersect(second_circle);
        CHECK(result.size() == expected_points.size());
        for (int i = 0; i < result.size(); i++) {
            CHECK(abs(result[i].x() - expected_points[i].x()) < EPS);
            CHECK(abs(result[i].y() - expected_points[i].y()) < EPS);
        }
    }

    SECTION("No intersection") { // NOLINT
        Circle first_circle(0.0, 0.0, 3.0);

        Circle second_circle(5.0, 0.0, 1.0);

        std::vector<Point> result = first_circle.intersect(second_circle);
        CHECK(result.empty());
    }

    SECTION("Nested circles") { // NOLINT
        Circle first_circle(3.0, 3.0, 3.0);

        Circle second_circle(3.0, 3.0, 1.0);

        std::vector<Point> result = first_circle.intersect(second_circle);
        CHECK(result.empty());
    }

}