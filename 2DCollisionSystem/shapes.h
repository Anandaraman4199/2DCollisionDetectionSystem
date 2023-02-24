#pragma once
#include <vector2f.h>
#include <SFML/Graphics.hpp>

struct Line
{
    Vector2f point, direction;

    sf::Vertex line[2];

    Line(Vector2f Point, Vector2f Direction) :point(Point), direction(Direction)
    {

        Vector2f directionMultiplied = Direction;
        directionMultiplied.scale(10000);
        Vector2f pointA = Point - directionMultiplied;
        Vector2f pointB = Point + directionMultiplied;

        sf::Vector2f linePointA(pointA.x, pointA.y);
        sf::Vector2f linePointB(pointB.x, pointB.y);
        line[0] = sf::Vertex(sf::Vector2f(linePointA));
        line[1] = sf::Vertex(sf::Vector2f(linePointB));

    }

};

struct LineSegment
{
    sf::Vertex line[2];

    Vector2f point1, point2;

    LineSegment(Vector2f Point1, Vector2f Point2) :point1(Point1), point2(Point2)
    {
        line[0] = sf::Vertex(sf::Vector2f(point1.x, point1.y));
        line[1] = sf::Vertex(sf::Vector2f(point2.x, point2.y));
    }

};

struct Circle
{
    Vector2f centre;
    float radius;

    sf::CircleShape circle;

    Circle(Vector2f Centre, float Radius) :centre(Centre), radius(Radius)
    {
        circle.setPosition(sf::Vector2f(centre.x, centre.y));
        circle.setRadius(radius);
        circle.setPointCount(radius / 2);
        circle.setOrigin(sf::Vector2f(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2));
    }

    void moveUp()
    {
        centre.y = centre.y - 0.1;
        circle.setPosition(sf::Vector2f(centre.x, centre.y));
    }

    void moveDown()
    {
        centre.y = centre.y + 0.1;
        circle.setPosition(sf::Vector2f(centre.x, centre.y));
    }

    void moveLeft()
    {
        centre.x = centre.x - 0.1;
        circle.setPosition(sf::Vector2f(centre.x, centre.y));
    }

    void moveRight()
    {
        centre.x = centre.x + 0.1;
        circle.setPosition(sf::Vector2f(centre.x, centre.y));
    }

};

struct Rectangle
{
    Vector2f origin;
    float width, height;
    sf::RectangleShape rect;

    Rectangle(float Width, float Height, Vector2f Origin) :width(Width), height(Height), origin(Origin)
    {
        rect.setPosition(sf::Vector2f(Origin.x, Origin.y));
        rect.setSize(sf::Vector2f(Width, Height));
        rect.setFillColor(sf::Color::White);
    }

    void moveUp()
    {
        origin.y = origin.y - 0.1;
        rect.setPosition(sf::Vector2f(origin.x, origin.y));
    }

    void moveDown()
    {
        origin.y = origin.y + 0.1;
        rect.setPosition(sf::Vector2f(origin.x, origin.y));
    }

    void moveLeft()
    {
        origin.x = origin.x - 0.1;
        rect.setPosition(sf::Vector2f(origin.x, origin.y));
    }

    void moveRight()
    {
        origin.x = origin.x + 0.1;
        rect.setPosition(sf::Vector2f(origin.x, origin.y));
    }

};

struct Oriented_Rectangle
{
    Vector2f centre, halfExtend;
    float angle;

    Vector2f nvertex[4];

    Vector2f vertex[4];

    sf::Vertex rect[4];

    Oriented_Rectangle(Vector2f Centre, Vector2f HalfExtend, float Angle) :centre(Centre), halfExtend(HalfExtend), angle(Angle)
    {
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0: nvertex[i] = HalfExtend;
                break;

            case 1: nvertex[i] = Vector2f(HalfExtend.x, -HalfExtend.y);
                break;

            case 2: nvertex[i] = HalfExtend.negate_vector();
                break;

            case 3: nvertex[i] = Vector2f(-HalfExtend.x, HalfExtend.y);
                break;

            }

            nvertex[i].rotate(Angle);
            vertex[i] = Centre + nvertex[i];
            rect[i] = sf::Vector2f(vertex[i].x, vertex[i].y);
        }

    }

    void update()
    {
        for (int i = 0; i < 4; i++)
        {
            vertex[i] = centre + nvertex[i];
            rect[i] = sf::Vector2f(vertex[i].x, vertex[i].y);
        }

    }

    void moveUp()
    {
        centre.y = centre.y - 0.1;
        this->update();

    }

    void moveDown()
    {
        centre.y = centre.y + 0.1;
        this->update();

    }
    void moveLeft()
    {
        centre.x = centre.x - 0.1;
        this->update();

    }
    void moveRight()
    {
        centre.x = centre.x + 0.1;
        this->update();

    }
    void rotateLeft()
    {
        angle = angle + 0.1f;
        for (int i = 0; i < 4; i++)
        {
            nvertex[i].rotate(0.1);
        }
        this->update();
    }
    void rotateRight()
    {
        angle = angle - 0.1f;
        for (int i = 0; i < 4; i++)
        {
            nvertex[i].rotate(0.1);
        }
        this->update();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(rect, 4, sf::Quads);
    }

};