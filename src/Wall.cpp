#include "EstheticEffectDebris.h"
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

void Wall::createDebris()
{
    //sf::Vector2f pos = m_body.getPosition();
    sf::Vector2f pos = sf::Vector2f(m_body.getXMin() + WALL_DEBRIS_SIZE / 2.f, m_body.getYMin() + WALL_DEBRIS_SIZE / 2.f);
    unsigned int xNumber = m_body.getRectangle().x / WALL_DEBRIS_SIZE;
    unsigned int yNumber = m_body.getRectangle().y / WALL_DEBRIS_SIZE;

    for(unsigned int i=0; i<xNumber; i++)
    {
        for(unsigned int j=0; j<yNumber; j++)
        {
            EstheticEffectDebris* ees = new EstheticEffectDebris(WALL_DEBRIS_DURATION);
            ees->setPosition(sf::Vector2f(pos.x+i*WALL_DEBRIS_SIZE,pos.y+j*WALL_DEBRIS_SIZE));
            ees->setRectangle(sf::Vector2f(WALL_DEBRIS_SIZE,WALL_DEBRIS_SIZE));
            ees->setColor(WALL_DESTRUCTIBLE_COLOR);
            ees->setAngularVelocity(rand()%200-100);
            ees->setVelocity(sf::Vector2f(rand()%100-50,rand()%100-50));
            m_aEstheticEffect.push_back(ees);
        }
    }
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

