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

bool checkCollision(Oriented_Rectangle& first, Oriented_Rectangle& second);

bool checkCollision(Rectangle& first, Rectangle& second);

bool checkCollision(Circle& first, Circle& second);

bool checkCollision(Line& first, Line& second);

bool checkCollision(LineSegment& first, LineSegment& second);

bool checkCollision(Circle& circle, Vector2f& point);

bool checkCollision(Circle& circle, Line& line);

bool checkCollision(Circle& circle, LineSegment& segment);

bool checkCollision(Circle& circle, Rectangle& rectangle);

bool checkCollision(Circle& circle, Oriented_Rectangle& orientedRectangle);

bool checkCollision(Rectangle& rectangle, Vector2f& point);

bool checkCollision(Rectangle& rectangle, Line& line);

bool checkCollision(Rectangle& rectangle, LineSegment& segment);

bool checkCollision(Rectangle& rect, Oriented_Rectangle& orientedRect);

bool checkCollision(Vector2f& point, Line& line);

bool checkCollision(Vector2f& point, LineSegment& segment);

bool checkCollision(Vector2f& point, Oriented_Rectangle& orientedRect);

bool checkCollision(Line& line, LineSegment& segment);

bool checkCollision(Line& line, Oriented_Rectangle& orientedRect);

bool checkCollision(LineSegment& segment, Oriented_Rectangle& orientedRect);