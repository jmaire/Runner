#include "Exit.h"
#include "Visitor.h"

Exit::Exit()
: Doodad()
, m_reached(false)
{
    m_body.setRectangle(EXIT_RECTANGLE);
}

Exit::Exit(sf::Vector2f pos)
: Exit()
{
    m_body.setPosition(pos);
}

Exit::~Exit()
{}

bool Exit::isReached(void)
{
    return m_reached;
}

void Exit::setReached(bool reached)
{
    m_reached = reached;
}

void Exit::accept(Visitor& v)
{
	v.visitExit(this);
}

void Exit::render(sf::RenderWindow& window)
{
	unsigned int height = window.getSize().y;

	sf::RectangleShape shape;
	shape.setSize(m_body.getRectangle());
	sf::Vector2f pos = m_body.getPosition();
	shape.setPosition(pos.x, height-pos.y - m_body.getRectangle().y);
	shape.setFillColor(EXIT_COLOR);
	window.draw(shape);
}

