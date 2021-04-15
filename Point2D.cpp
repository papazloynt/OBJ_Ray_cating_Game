#include "Point2D.h"
#include <cmath>

Point2D Point2D::operator+(const Point2D& point2D) const
{
    return Point2D{ this->x + point2D.x, this->y + point2D.y };
}

Point2D Point2D::operator-(const Point2D& point2D) const
{
    return Point2D{ this->x - point2D.x, this->y - point2D.y };
}

Point2D Point2D::operator*(double number) const
{
    return Point2D{ this->x * number, this->y * number };
}

Point2D Point2D::operator/(double number) const
{
    return Point2D{ this->x * number, this->y * number };
}

Point2D& Point2D::operator= (const Point2D& point2D)
{
    this->x = point2D.x;
    this->y = point2D.y;
    return *this;
}

Point2D& Point2D::operator+=(const Point2D& point2D)
{
    this->x += point2D.x;
    this->y += point2D.y;
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& point2D)
{
    this->x -= point2D.x;
    this->y -= point2D.y;
    return *this;
}

Point2D& Point2D::operator*=(double number)
{
    this->x *= number;
    this->y *= number;
    return *this;
}

Point2D& Point2D::operator/=(double number)
{
    this->x /= number;
    this->y /= number;
    return *this;
}

bool Point2D::operator<(const Point2D& point2D) const {
    return x < point2D.x && y < point2D.y;
}

bool Point2D::operator==(const Point2D& point2D)
{
    return this == &point2D || (*this - point2D).sqrAbs() < 0.0000000001;
}

bool Point2D::operator!=(const Point2D& point2D)
{
    return this != &point2D && (*this - point2D).sqrAbs() > 0.0000000001;
}

double Point2D::operator*(const Point2D& point2D) const
{
    return this->x * point2D.x + this->y * point2D.y;
}

double Point2D::cross(const Point2D& point2D) const
{
    return this->x * point2D.y - this->y * point2D.x;
}

Point2D Point2D::normalize() const
{
    double length = this->abs();
    return Point2D{ this->x / length, this->y / length };
}

double Point2D::sqrAbs() const
{
    return x * x + y * y;
}

double Point2D::abs() const
{
    return sqrt(x * x + y * y);
}

int signum(double n) {
    return n >= 0 ? 1 : -1;
}

double Point2D::getAngle(const Point2D& b) const {
    Point2D a = normalize();
    Point2D d = b.normalize();

    double result = asin(a.x*d.y - a.y*d.x);

    return result;
}