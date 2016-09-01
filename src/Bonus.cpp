#include "Bonus.h"
#include "tools.h"

Bonus::Bonus()
: Doodad()
{
    m_body.setRectangle(BONUS_RECTANGLE);
}

Bonus::Bonus(sf::Vector2f pos)
: Bonus()
{
    m_body.setPosition(pos);
}

Bonus::~Bonus()
{}

void Bonus::accept(Visitor& v)
{
	v.visitBonus(this);
}

void Bonus::collisionEvent(Doodad* doodad)
{
	VisitorBonus v = VisitorBonus(this);
	doodad->accept(v);
}

void Bonus::render(sf::RenderWindow& window)
{
	if(1 == m_state)
	{
		return;
	}

	sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();
    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);

	shape.setFillColor(BONUS_COLOR);

	window.draw(shape);
}

