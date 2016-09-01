#include "Wall.h"
#include "tools.h"

Wall::Wall()
: Doodad()
, m_isDestructible(false)
, m_isDestroyed(false)
{
    m_body.setRestitution(1.f);
}

Wall::Wall(sf::Vector2f rec, sf::Vector2f pos)
: Wall()
{
    m_body.setRectangle(rec);
    m_body.setPosition(pos);
}

Wall::~Wall()
{}

void Wall::setDestructible(bool isDes)
{
    m_isDestructible = isDes;
}

bool Wall::isDestructible()
{
    return m_isDestructible;
}

void Wall::accept(Visitor& v)
{
	v.visitWall(this);
}

void Wall::collisionEvent(Doodad& doodad)
{
	VisitorWall v = VisitorWall(this);
	doodad.accept(v);
}

void Wall::render(sf::RenderWindow& window)
{
	sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();

    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);

	if(m_isDestructible)
        shape.setFillColor(WALL_DESTRUCTIBLE_COLOR);
    else
        shape.setFillColor(WALL_INDESTRUCTIBLE_COLOR);

	window.draw(shape);
}

