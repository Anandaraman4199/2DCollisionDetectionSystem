#include <vector2f.h>
#include <cmath>
#include <string>

// Constant variable for PI

const float PI = 3.14;

// Angle to Radian conversion.

float angleToradian(float angle)
{
    return angle * PI / 180;
}

//Addition overload function

Vector2f Vector2f::operator+(Vector2f& other) const
{
    return Vector2f(x + other.x, y + other.y);
}

//Subtraction Overload function

Vector2f Vector2f::operator -(Vector2f& other) const
{
    return Vector2f(x - other.x, y - other.y);
}

//This will return the unit vector by dividing its x and y by its length.

Vector2f Vector2f::unitVector() const
{
    return Vector2f(x / this->length(), y / this->length());
}

//Comparision overload function

bool Vector2f::operator ==(Vector2f& other) const
{
    return (x == other.x) && (y == other.y);
}

//This function returns the length of the given vector by the square rooting the dot product of self.

float Vector2f::length() const
{
    return sqrtf(x * x + y * y);
}

//Scaling vector function

void Vector2f::scale(float scale)
{
    x = scale * x;
    y = scale * y;
}

//This function will rotate the vector by the given angle

void Vector2f::rotate(float angle)
{
    float X = x * cosf(angleToradian(angle)) - y * sinf(angleToradian(angle));
    float Y = x * sinf(angleToradian(angle)) + y * cosf(angleToradian(angle));
    x = X;
    y = Y;
}

//This function project the given vector onto the another given vector 

Vector2f projection(Vector2f& project, Vector2f& onto)
{
    float distance = dotproduct(project, onto) / dotproduct(onto, onto);
    Vector2f projected = onto;
    projected.scale(distance);
    return projected;
}

//This will return the dot product 

float dotproduct(Vector2f& project, Vector2f& onto)
{
    return project.x * onto.x + project.y * onto.y;
}

// << overload function to print the x and y values of vector in ostream.

std::ostream& operator<<(std::ostream& os, const Vector2f& vector)
{
    os << " X : " << vector.x << "  ;  Y : " << vector.y << std::endl;
    return os;
}