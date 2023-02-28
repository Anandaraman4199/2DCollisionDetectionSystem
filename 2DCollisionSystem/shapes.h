#pragma once
#include <vector2f.h>
#include <SFML/Graphics.hpp>

namespace Shapes
{
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

        void moveUp()
        {
            point.y = point.y - 0.1;
            Vector2f directionMultiplied = direction;
            directionMultiplied.scale(10000);
            Vector2f pointA = point - directionMultiplied;
            Vector2f pointB = point + directionMultiplied;

            sf::Vector2f linePointA(pointA.x, pointA.y);
            sf::Vector2f linePointB(pointB.x, pointB.y);
            line[0] = sf::Vertex(sf::Vector2f(linePointA));
            line[1] = sf::Vertex(sf::Vector2f(linePointB));
        }

        void moveDown()
        {
            point.y = point.y + 0.1;
            Vector2f directionMultiplied = direction;
            directionMultiplied.scale(10000);
            Vector2f pointA = point - directionMultiplied;
            Vector2f pointB = point + directionMultiplied;

            sf::Vector2f linePointA(pointA.x, pointA.y);
            sf::Vector2f linePointB(pointB.x, pointB.y);
            line[0] = sf::Vertex(sf::Vector2f(linePointA));
            line[1] = sf::Vertex(sf::Vector2f(linePointB));
        }

        void moveLeft()
        {
            point.x = point.x - 0.1;
            Vector2f directionMultiplied = direction;
            directionMultiplied.scale(10000);
            Vector2f pointA = point - directionMultiplied;
            Vector2f pointB = point + directionMultiplied;

            sf::Vector2f linePointA(pointA.x, pointA.y);
            sf::Vector2f linePointB(pointB.x, pointB.y);
            line[0] = sf::Vertex(sf::Vector2f(linePointA));
            line[1] = sf::Vertex(sf::Vector2f(linePointB));
        }

        void moveRight()
        {
            point.x = point.x + 0.1;
            Vector2f directionMultiplied = direction;
            directionMultiplied.scale(10000);
            Vector2f pointA = point - directionMultiplied;
            Vector2f pointB = point + directionMultiplied;

            sf::Vector2f linePointA(pointA.x, pointA.y);
            sf::Vector2f linePointB(pointB.x, pointB.y);
            line[0] = sf::Vertex(sf::Vector2f(linePointA));
            line[1] = sf::Vertex(sf::Vector2f(linePointB));
        }

        void setColour(sf::Color colour)
        {
            line[0].color = colour;
            line[1].color = colour;
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(line, 2, sf::Lines);
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

        void moveUp()
        {
            point1.y = point1.y - 0.1;
            point2.y = point2.y - 0.1;
            line[0] = sf::Vertex(sf::Vector2f(point1.x, point1.y));
            line[1] = sf::Vertex(sf::Vector2f(point2.x, point2.y));
        }

        void moveDown()
        {
            point1.y = point1.y + 0.1;
            point2.y = point2.y + 0.1;
            line[0] = sf::Vertex(sf::Vector2f(point1.x, point1.y));
            line[1] = sf::Vertex(sf::Vector2f(point2.x, point2.y));
        }

        void moveLeft()
        {
            point1.x = point1.x - 0.1;
            point2.x = point2.x - 0.1;
            line[0] = sf::Vertex(sf::Vector2f(point1.x, point1.y));
            line[1] = sf::Vertex(sf::Vector2f(point2.x, point2.y));
        }

        void moveRight()
        {
            point1.x = point1.x + 0.1;
            point2.x = point2.x + 0.1;
            line[0] = sf::Vertex(sf::Vector2f(point1.x, point1.y));
            line[1] = sf::Vertex(sf::Vector2f(point2.x, point2.y));
        }

        void setColour(sf::Color colour)
        {
            line[0].color = colour;
            line[1].color = colour;
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(line, 2, sf::Lines);
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

        void setColour(sf::Color colour)
        {
            circle.setFillColor(colour);
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(circle);
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

        void setColour(sf::Color colour)
        {
            rect.setFillColor(colour);
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(rect);
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

        void setColour(sf::Color colour)
        {
            rect[0].color = colour;
            rect[1].color = colour;
            rect[2].color = colour;
            rect[3].color = colour;
        }

    };
}