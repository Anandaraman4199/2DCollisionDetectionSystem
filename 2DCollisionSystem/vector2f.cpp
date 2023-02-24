#include <vector2f.h>
#include <cmath>
#include <string>

const float PI = 3.14;

float angleToradian(float angle)
{
    return angle * PI / 180;
}

Vector2f Vector2f::operator+(Vector2f& other) const
{
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator -(Vector2f& other) const
{
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::unitVector() const
{
    return Vector2f(x / this->length(), y / this->length());
}

bool Vector2f::operator ==(Vector2f& other) const
{
    return (x == other.x) && (y == other.y);
}

float Vector2f::length() const
{
    return sqrtf(x * x + y * y);
}

void Vector2f::scale(float scale)
{
    x = scale * x;
    y = scale * y;
}

void Vector2f::rotate(float angle)
{
    float X = x * cosf(angleToradian(angle)) - y * sinf(angleToradian(angle));
    float Y = x * sinf(angleToradian(angle)) + y * cosf(angleToradian(angle));
    x = X;
    y = Y;
}

Vector2f projection(Vector2f& project, Vector2f& onto)
{
    float distance = dotproduct(project, onto) / dotproduct(onto, onto);
    Vector2f projected = onto;
    projected.scale(distance);
    return projected;
}

float dotproduct(Vector2f& project, Vector2f& onto)
{
    return project.x * onto.x + project.y * onto.y;
}

std::ostream& operator<<(std::ostream& os, const Vector2f& vector)
{
    os << " X : " << vector.x << "  ;  Y : " << vector.y << std::endl;
    return os;
}