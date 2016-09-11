#include "tools.h"

sf::Vector2f convertPositionToWindowCoordonates(sf::RenderWindow& window, sf::Vector2f position)
{
	unsigned int windowHeight = window.getSize().y;
    return sf::Vector2f(position.x, (float)windowHeight - position.y);
}

sf::Vector2f getCircleCenter(float radius)
{
    return sf::Vector2f(radius, radius);
}

sf::Vector2f getRectangleCenter(sf::Vector2f rectangle)
{
    return sf::Vector2f(rectangle.x / 2.f, rectangle.y / 2.f);
}

sf::CircleShape getCircleShapeForWindow(sf::RenderWindow& window, float radius, sf::Vector2f position)
{
    sf::CircleShape shape = sf::CircleShape(radius);

    shape.setOrigin(getCircleCenter(radius));
    shape.setPosition(convertPositionToWindowCoordonates(window, position));

    return shape;
}

sf::RectangleShape getRectangleShapeForWindow(sf::RenderWindow& window, sf::Vector2f rectangle, sf::Vector2f position)
{
    sf::RectangleShape shape = sf::RectangleShape(rectangle);

    shape.setOrigin(getRectangleCenter(rectangle));
    shape.setPosition(convertPositionToWindowCoordonates(window, position));

    return shape;
}
