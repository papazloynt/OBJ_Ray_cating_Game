#ifndef OBJGAME_POINT2D_H
#define OBJGAME_POINT2D_H

struct Point2D
{
    double x;
    double y;

    Point2D() = default;
    Point2D(double x, double y): x(x), y(y) {
    }

    Point2D operator+(const Point2D& point2D) const;
    Point2D operator-(const Point2D& point2D) const;
    Point2D operator*(double number) const;
    Point2D operator/(double number) const;

    Point2D& operator=(const Point2D& point2D);

    Point2D& operator+=(const Point2D& point2D);
    Point2D& operator-=(const Point2D& point2D);
    Point2D& operator*=(double number);
    Point2D& operator/=(double number);

    bool operator==(const Point2D& point2D);
    bool operator!=(const Point2D& point2D);
    bool operator<(const Point2D& point2D) const;

    double operator*(const Point2D& point2D) const;
    double cross(const Point2D& point2D) const;
    // normalize vector
    Point2D normalize() const;
    // squared vector length
    double sqrAbs() const;
    // vector length
    double abs() const;

    double getAngle(const Point2D& b) const;
};

#endif //OBJGAME_POINT2D_H