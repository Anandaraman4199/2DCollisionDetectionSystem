#pragma once
#include <shapes.h>

struct Range
{
    float min, max;

    Range()
    {
        min = 0;
        max = 0;
    }

    Range(float Min, float Max) :min(Min), max(Max)
    {

    }

    void sort()
    {
        if (min > max)
        {
            float temp = max;
            max = min;
            min = temp;
        }
    }
};

Range range_hull(Range& first, Range& second);

bool checkCollision(Shapes::Oriented_Rectangle& first, Shapes::Oriented_Rectangle& second);

bool checkCollision(Shapes::Rectangle& first, Shapes::Rectangle& second);

bool checkCollision(Shapes::Circle& first, Shapes::Circle& second);

bool checkCollision(Shapes::Line& first, Shapes::Line& second);

bool checkCollision(Shapes::LineSegment& first, Shapes::LineSegment& second);

bool checkCollision(Shapes::Circle& circle, Vector2f& point);

bool checkCollision(Shapes::Circle& circle, Shapes::Line& line);

bool checkCollision(Shapes::Circle& circle, Shapes::LineSegment& segment);

bool checkCollision(Shapes::Circle& circle, Shapes::Rectangle& rectangle);

bool checkCollision(Shapes::Circle& circle, Shapes::Oriented_Rectangle& orientedRectangle);

bool checkCollision(Shapes::Rectangle& rectangle, Vector2f& point);

bool checkCollision(Shapes::Rectangle& rectangle, Shapes::Line& line);

bool checkCollision(Shapes::Rectangle& rectangle, Shapes::LineSegment& segment);

bool checkCollision(Shapes::Rectangle& rect, Shapes::Oriented_Rectangle& orientedRect);

bool checkCollision(Vector2f& point, Shapes::Line& line);

bool checkCollision(Vector2f& point, Shapes::LineSegment& segment);

bool checkCollision(Vector2f& point, Shapes::Oriented_Rectangle& orientedRect);

bool checkCollision(Shapes::Line& line, Shapes::LineSegment& segment);

bool checkCollision(Shapes::Line& line, Shapes::Oriented_Rectangle& orientedRect);

bool checkCollision(Shapes::LineSegment& segment, Shapes::Oriented_Rectangle& orientedRect);