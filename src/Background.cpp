#include <SFML/Graphics/RectangleShape.hpp>
#include "Background.h"
#include "tools.h"

Background::Background()
: Entity()
, m_layoutDepth(0)
{}

Background::~Background()
{}

void Background::setDepth(int depth)
{
	m_layoutDepth = depth;
}

void Background::setColor(sf::Color color)
{
	m_color = color;
}

void Background::update(float dt)
{
	m_body.update(dt);
}

void Background::render(sf::RenderWindow& window)
{
	/*
	sf::Vector2f rectangle = m_body.getRectangle();

    sf::ConvexShape shape = sf::ConvexShape(3);
    shape.setPoint(0, sf::Vector2f(0.f, 0.f));
    shape.setPoint(1, sf::Vector2f(0.f, rectangle.x));
    shape.setPoint(2, sf::Vector2f(rectangle.x / 2.f, rectangle.y);

	window.draw(shape);
	*/

	sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();
    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);
	shape.setFillColor(m_color);

	window.draw(shape);
}
