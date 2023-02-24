#include <collisiondetection.h>

int main()
{
    const int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;
    const int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GameMath", sf::Style::Fullscreen);

    sf::Event evnt;

    Rectangle rect(100, 300, Vector2f(1000, 600));

    Oriented_Rectangle oriented_rect(Vector2f(1750, 890), Vector2f(150, 250), 60);


    while (window.isOpen())
    {
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rect.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rect.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rect.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rect.moveDown();
        }


        if (checkCollision(rect, oriented_rect))
        {
            rect.rect.setFillColor(sf::Color::Red);
            oriented_rect.rect[0].color = sf::Color::Red;
            oriented_rect.rect[1].color = sf::Color::Red;
            oriented_rect.rect[2].color = sf::Color::Red;
            oriented_rect.rect[3].color = sf::Color::Red;

        }
        else
        {
            rect.rect.setFillColor(sf::Color::White);
            oriented_rect.rect[0].color = sf::Color::White;
            oriented_rect.rect[1].color = sf::Color::White;
            oriented_rect.rect[2].color = sf::Color::White;
            oriented_rect.rect[3].color = sf::Color::White;
        }

        window.clear();

        window.draw(rect.rect);

        oriented_rect.draw(window);


        window.display();

    }
    return 0;
}