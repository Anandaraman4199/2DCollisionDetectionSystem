#pragma once
#include <iostream>

struct Vector2f
{
    float x, y;

    Vector2f()
    {
        x = 0;
        y = 0;

    }

    Vector2f(float X, float Y) :x(X), y(Y)
    {

    }

    Vector2f operator +(Vector2f& other) const;

    Vector2f operator -(Vector2f& other) const;

    bool operator ==(Vector2f& other) const;

    Vector2f unitVector() const;

    float length() const;

    void scale(float scale);

    void rotate(float angle);

    Vector2f negate_vector()
    {
        return Vector2f(-x, -y);
    }

};



float dotproduct(Vector2f& project, Vector2f& onto);

Vector2f projection(Vector2f& project, Vector2f& onto);

std::ostream& operator<<(std::ostream& os, const Vector2f& vector);