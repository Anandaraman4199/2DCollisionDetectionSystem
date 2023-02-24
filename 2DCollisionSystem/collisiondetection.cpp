#include <collisiondetection.h>

Range range_hull(Range& first, Range& second)
{
    return Range(first.min<second.min ? first.min : second.min, second.max>first.max ? second.max : first.max);
}

//Rectangle Collision Detection

bool checkCollision(Rectangle& first, Rectangle& second)
{
    float minSA = first.origin.x;
    float maxSA = first.origin.x + first.width;
    float minUA = first.origin.y;
    float maxUA = first.origin.y + first.height;

    float minSB = second.origin.x;
    float maxSB = second.origin.x + second.width;
    float minUB = second.origin.y;
    float maxUB = second.origin.y + second.height;

    bool sideCollision = (minSA <= maxSB) && (minSB <= maxSA);
    bool verticalCollision = (minUA <= maxUB) && (minUB <= maxUA);

    return sideCollision && verticalCollision;
}

//Circle Collision Detection

bool checkCollision(Circle& first, Circle& second)
{
    return ((second.centre - first.centre).length()) <= (first.radius + second.radius);
}

//Line Collision Detection

bool parallelVectorCheck(Vector2f& first, Vector2f& second)
{
    Vector2f rotatedDirection = second;
    rotatedDirection.rotate(90);
    if (dotproduct(rotatedDirection, first))
    {
        return false;
    }
    return true;
}

bool checkCollision(Line& first, Line& second)
{
    if (!parallelVectorCheck(first.direction, second.direction))
    {
        return true;
    }

    Vector2f differenceVector = first.point - second.point;

    if (parallelVectorCheck(differenceVector, first.direction))
    {
        return true;
    }

    return false;

}

bool on_one_side(Line& Axis, LineSegment& otherSegment)
{
    Vector2f rotatedVector = Axis.direction;
    rotatedVector.rotate(90);
    Vector2f point1frombase = otherSegment.point1 - Axis.point;
    Vector2f point2frombase = otherSegment.point2 - Axis.point;
    return dotproduct(rotatedVector, point1frombase) * dotproduct(rotatedVector, point2frombase) > 0;
}

Range project_segment(Vector2f direction_unit_vector, LineSegment segment)
{
    Range project(dotproduct(direction_unit_vector, segment.point1), dotproduct(direction_unit_vector, segment.point2));
    project.sort();
    return project;
}

bool checkCollision(LineSegment& first, LineSegment& second)
{
    Line fAxis(first.point1, first.point2 - first.point1);
    if (on_one_side(fAxis, second))
    {
        return false;
    }
    Line sAxis(second.point1, second.point2 - second.point1);
    if (on_one_side(sAxis, first))
    {
        return false;
    }
    if (parallelVectorCheck(fAxis.direction, sAxis.direction))
    {

        Vector2f unitVector = fAxis.direction.unitVector();

        Range fRange = project_segment(unitVector, first);
        Range sRange = project_segment(unitVector, second);

        return (fRange.max >= sRange.min) && (sRange.max >= fRange.min);
    }
    else
    {
        return true;
    }

}

LineSegment oriented_rectangle_edge(Oriented_Rectangle& orientedRect, int edge)
{
    Vector2f point1(orientedRect.halfExtend);
    Vector2f point2(orientedRect.halfExtend);

    switch (edge)
    {
    case 0: point1 = point1.negate_vector();
        point2.y = -point2.y;
        break;

    case 1: point1.y = -point1.y;
        break;

    case 2: point1.x = -point1.x;
        break;

    default: point1 = point1.negate_vector();
        point2.x = -point2.x;
        break;

    }

    point1.rotate(orientedRect.angle);
    point2.rotate(orientedRect.angle);

    return LineSegment(point1 + orientedRect.centre, point2 + orientedRect.centre);

}

bool seperating_axis_oriented_rectangle(LineSegment& edge, Oriented_Rectangle& other)
{
    Vector2f axis = edge.point2 - edge.point1;
    axis = axis.unitVector();

    LineSegment second0edge = oriented_rectangle_edge(other, 0);
    LineSegment second2edge = oriented_rectangle_edge(other, 2);

    Range firstRange = project_segment(axis, edge);
    Range second0Range = project_segment(axis, second0edge);
    Range second2Range = project_segment(axis, second2edge);
    Range secondRange = range_hull(second0Range, second2Range);

    return (firstRange.max >= secondRange.min) && (secondRange.max >= firstRange.min);
}

bool checkCollision(Oriented_Rectangle& first, Oriented_Rectangle& second)
{
    LineSegment edge = oriented_rectangle_edge(first, 0);

    if (!seperating_axis_oriented_rectangle(edge, second))
    {
        return false;
    }

    edge = oriented_rectangle_edge(first, 1);

    if (!seperating_axis_oriented_rectangle(edge, second))
    {
        return false;
    }

    edge = oriented_rectangle_edge(second, 0);

    if (!seperating_axis_oriented_rectangle(edge, first))
    {
        return false;
    }

    edge = oriented_rectangle_edge(second, 1);

    return seperating_axis_oriented_rectangle(edge, first);

}

bool checkCollision(Circle& circle, Vector2f& point)
{
    return (point - circle.centre).length() <= circle.radius;
}

bool checkCollision(Circle& circle, Line& line)
{
    Vector2f line_to_circle = circle.centre - line.point;
    Vector2f project = projection(line_to_circle, line.direction);
    Vector2f nearest_point = line.point + project;

    return checkCollision(circle, nearest_point);
}

bool checkCollision(Circle& circle, LineSegment& segment)
{
    if (checkCollision(circle, segment.point1))
    {
        return true;
    }
    if (checkCollision(circle, segment.point2))
    {
        return true;
    }

    Vector2f distance = segment.point2 - segment.point1;
    Vector2f segmentToCircle = circle.centre - segment.point1;
    Vector2f project = projection(segmentToCircle, distance);
    Vector2f nearest = project + segment.point1;
    return checkCollision(circle, nearest) && project.length() <= distance.length() && dotproduct(project, distance) >= 0;


}

float clamp_on_range(float point, float min, float max)
{

    if (point < min)
    {
        return min;
    }

    if (point > max)
    {
        return max;
    }

    return point;

}

Vector2f nearest_vector(Vector2f point, Rectangle& rectangle)
{
    Vector2f clamped;
    clamped.x = clamp_on_range(point.x, rectangle.origin.x, rectangle.origin.x + rectangle.width);
    clamped.y = clamp_on_range(point.y, rectangle.origin.y, rectangle.origin.y + rectangle.height);
    return clamped;
}

bool checkCollision(Circle& circle, Rectangle& rectangle)
{
    Vector2f nearest = nearest_vector(circle.centre, rectangle);
    return checkCollision(circle, nearest);
}

bool checkCollision(Circle& circle, Oriented_Rectangle& orientedRectangle)
{
    Vector2f localRectSize = orientedRectangle.halfExtend;
    localRectSize.scale(2);
    Rectangle localRect(localRectSize.x, localRectSize.y, Vector2f(0, 0));
    Vector2f distance = circle.centre - orientedRectangle.centre;
    distance.rotate(-orientedRectangle.angle);
    Vector2f localCircleCentre = distance + orientedRectangle.halfExtend;

    Circle localCircle(localCircleCentre, circle.radius);

    return checkCollision(localCircle, localRect);
}

bool checkCollision(Rectangle& rectangle, Vector2f& point)
{
    return (point.x) >= rectangle.origin.x
        &&
        point.y >= rectangle.origin.y
        &&
        point.x <= rectangle.origin.x + rectangle.width
        &&
        point.y <= rectangle.origin.y + rectangle.height;

}

bool checkCollision(Rectangle& rectangle, Line& line)
{

    Vector2f rotated_direction = line.direction;
    rotated_direction.rotate(90);

    Vector2f rec1(rectangle.origin);
    Vector2f rec2(rectangle.origin.x, rectangle.origin.y + rectangle.height);
    Vector2f rec3(rectangle.origin.x + rectangle.width, rectangle.origin.y);
    Vector2f rec4(rectangle.origin.x + rectangle.width, rectangle.origin.y + rectangle.height);

    rec1 = rec1 - line.point;
    rec2 = rec2 - line.point;
    rec3 = rec3 - line.point;
    rec4 = rec4 - line.point;


    float dp1 = dotproduct(rec1, rotated_direction);
    float dp2 = dotproduct(rec2, rotated_direction);
    float dp3 = dotproduct(rec3, rotated_direction);
    float dp4 = dotproduct(rec4, rotated_direction);

    return (dp1 * dp4 <= 0) || (dp2 * dp3 <= 0);

}

bool checkCollision(Rectangle& rectangle, LineSegment& segment)
{

    Line sAxis(segment.point1, segment.point2 - segment.point1);
    if (!checkCollision(rectangle, sAxis))
    {
        return false;
    }
    Range rectanglex, segmentx, rectangley, segmenty;

    rectanglex.min = rectangle.origin.x;
    rectanglex.max = rectanglex.min + rectangle.width;
    segmentx.min = segment.point1.x;
    segmentx.max = segment.point2.x;

    if (!((rectanglex.min <= segmentx.max) && (rectanglex.max >= segmentx.min)))
    {
        return false;
    }

    rectangley.min = rectangle.origin.y;
    rectangley.max = rectangley.min + rectangle.height;
    segmenty.min = segment.point1.y;
    segmenty.max = segment.point2.y;

    if (!((rectangley.min <= segmenty.max) && (rectangley.max >= segmenty.min)))
    {
        return false;
    }

    return true;

}

/*Vector2f oriented_rectangle_corner(Oriented_Rectangle &orientedRect,int corner_no)
{
    Vector2f corner = orientedRect.halfExtend;
    switch(corner_no)
    {
        case 0: corner.negate_vector();
                break;

        case 1: corner.y = -corner.y;
                break;

        case 2: corner = orientedRect.halfExtend;
                break;

        default: corner.x = -corner.x;
                 break;
    }
    corner.rotate(orientedRect.angle);

    return (corner+orientedRect.centre);

}*/

float minimum(float A, float B)
{
    return A < B ? A : B;
}

float maximum(float A, float B)
{
    return A > B ? A : B;
}

Rectangle extend_bound_rectangle(Rectangle& bound, Vector2f& corner)
{
    Rectangle enlarged(0, 0, Vector2f(0, 0));
    enlarged.origin.x = minimum(bound.origin.x, corner.x);
    enlarged.origin.y = minimum(bound.origin.y, corner.y);
    enlarged.width = maximum(bound.origin.x + bound.width, corner.x);
    enlarged.height = maximum(bound.origin.y + bound.height, corner.y);

    enlarged.width = enlarged.width - enlarged.origin.x;
    enlarged.height = enlarged.height - enlarged.origin.y;

    return enlarged;

}


Rectangle oriented_rectangle_bound(Oriented_Rectangle& orientedRect)
{
    Rectangle bound(0, 0, orientedRect.centre);

    Vector2f corner;

    for (int i = 0; i < 4; i++)
    {
        corner = orientedRect.vertex[i];
        bound = extend_bound_rectangle(bound, corner);
    }

    return bound;

}

Vector2f rectangle_corner(Rectangle& rectangle, int corner_no)
{
    Vector2f corner = rectangle.origin;

    switch (corner_no)
    {
    case 0: break;

    case 1: corner.x += rectangle.width;
        break;

    case 2: corner.x += rectangle.width;
        corner.y += rectangle.height;
        break;

    default: corner.y += rectangle.height;
        break;

    }

    return corner;

}


bool seperating_axis_rectangle(Rectangle& rectangle, LineSegment& edge)
{
    Vector2f axis = edge.point2 - edge.point1;

    LineSegment rEdge0(rectangle_corner(rectangle, 0), rectangle_corner(rectangle, 1));
    LineSegment rEdge1(rectangle_corner(rectangle, 2), rectangle_corner(rectangle, 3));

    Range Edge0range = project_segment(axis, rEdge0);
    Range Edge1range = project_segment(axis, rEdge1);
    Range AxisRange = project_segment(axis, edge);

    Range projected = range_hull(Edge0range, Edge1range);

    return (AxisRange.min <= projected.max) && (AxisRange.max >= projected.min);


}

bool checkCollision(Rectangle& rect, Oriented_Rectangle& orientedRect)
{
    Rectangle bound = oriented_rectangle_bound(orientedRect);

    if (!checkCollision(rect, bound))
    {
        return false;
    }

    LineSegment edge = oriented_rectangle_edge(orientedRect, 0);

    if (!seperating_axis_rectangle(rect, edge))
    {
        return false;
    }

    edge = oriented_rectangle_edge(orientedRect, 1);

    return seperating_axis_rectangle(rect, edge);

}

bool checkCollision(Vector2f& point, Line& line)
{
    if (point == line.point)
    {
        return true;
    }
    Vector2f lineToPoint = point - line.point;
    return parallelVectorCheck(lineToPoint, line.direction);

}

bool checkCollision(Vector2f& point, LineSegment& segment)
{
    Vector2f distance = segment.point2 - segment.point1;
    Vector2f toPoint = point - segment.point1;
    Vector2f projected = projection(toPoint, distance);
    return parallelVectorCheck(toPoint, projected) && projected.length() <= distance.length() && dotproduct(projected, distance) >= 0;
}

bool checkCollision(Vector2f& point, Oriented_Rectangle& orientedRect)
{
    Rectangle localRect(orientedRect.halfExtend.x * 2, orientedRect.halfExtend.y * 2, Vector2f(0, 0));
    Vector2f localPoint = point - orientedRect.centre;
    localPoint.rotate(-orientedRect.angle);
    localPoint = localPoint + orientedRect.halfExtend;

    return checkCollision(localRect, localPoint);
}

bool checkCollision(Line& line, LineSegment& segment)
{
    return !on_one_side(line, segment);
}

bool checkCollision(Line& line, Oriented_Rectangle& orientedRect)
{
    Rectangle localRect(orientedRect.halfExtend.x * 2, orientedRect.halfExtend.y * 2, Vector2f(0, 0));

    Vector2f localLineBase = line.point - orientedRect.centre;
    localLineBase.rotate(-orientedRect.angle);
    localLineBase = localLineBase + orientedRect.halfExtend;

    Vector2f localLineDirection = line.direction;
    line.direction.rotate(-orientedRect.angle);

    Line localLine(localLineBase, localLineDirection);

    return checkCollision(localRect, localLine);

}

bool checkCollision(LineSegment& segment, Oriented_Rectangle& orientedRect)
{
    Rectangle localRect(orientedRect.halfExtend.x * 2, orientedRect.halfExtend.y * 2, Vector2f(0, 0));

    Vector2f localSegmentPoint1 = segment.point1 - orientedRect.centre;
    localSegmentPoint1.rotate(-orientedRect.angle);
    localSegmentPoint1 = localSegmentPoint1 + orientedRect.halfExtend;

    Vector2f localSegmentPoint2 = segment.point2 - orientedRect.centre;
    localSegmentPoint2.rotate(-orientedRect.angle);
    localSegmentPoint2 = localSegmentPoint2 + orientedRect.halfExtend;

    LineSegment localSegment(localSegmentPoint1, localSegmentPoint2);

    return checkCollision(localRect, localSegment);

}