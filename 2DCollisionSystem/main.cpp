#include <collisiondetection.h>

int main()
{

// Get Screen Size

    const int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;
    const int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;

// Create window

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GameMath", sf::Style::Fullscreen);

    sf::Event evnt;

// Create any two shapes from Shapes namespace to detect collision

    Shapes::Rectangle rect(100, 300, Vector2f(1000, 600));

    Shapes::Oriented_Rectangle oriented_rect(Vector2f(1750, 890), Vector2f(150, 250), 60);

    while (window.isOpen())
    {
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
            {
                window.close();
            }
        }

// Keybindings for the movements for the shapes

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

//Checking collision for the shapes

        if (checkCollision(rect, oriented_rect))
        {

//Changing the color by custom function called setColor to see the collision

            rect.setColour(sf::Color::Red);
            oriented_rect.setColour(sf::Color::Red);


        }
        else
        {

//Changing color

            rect.setColour(sf::Color::White);
            oriented_rect.setColour(sf::Color::White);
        }

        window.clear();

//Calling the custom function to render the shapes

        rect.draw(window);

        oriented_rect.draw(window);


        window.display();

    }
    return 0;
}