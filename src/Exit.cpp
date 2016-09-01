#include "Exit.h"

Exit::Exit()
: Doodad()
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

void Exit::accept(Visitor& v)
{
	v.visitExit(this);
}

void Exit::collisionEvent(Doodad* doodad)
{
	VisitorExit v = VisitorExit(this);
	doodad->accept(v);
}
/*
void Exit::update(float dt)
{
	m_body.update(dt);
	// TODO animation
}
*/
void Exit::render(sf::RenderWindow& window)
{
	if(1 == m_state)
	{
		return;
	}

	unsigned int height = window.getSize().y;

	sf::RectangleShape shape;
	shape.setSize(m_body.getRectangle());
	sf::Vector2f pos = m_body.getPosition();
	shape.setPosition(pos.x, height-pos.y - m_body.getRectangle().y);
	shape.setFillColor(EXIT_COLOR);
	window.draw(shape);
}

