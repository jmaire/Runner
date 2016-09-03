#include <math.h>

#include <Doodad.h>

Doodad::Doodad()
: Entity()
{}

Doodad::~Doodad()
{}

bool Doodad::isBetweenBorder(float borderLeft, float borderRight, float borderBottom)
{
	if(m_body.getXMax() < borderLeft)
		return false;

	if(m_body.getXMin() > borderRight)
		return false;

	if(m_body.getYMax() < borderBottom)
		return false;

	return true;
}

bool Doodad::isDoodadOn(Doodad& doodad)
{
	sf::Vector2f groundRec = sf::Vector2f(m_body.getRectangle().x, COLLISION_APPROXIMATION);
	sf::Vector2f groundPos = sf::Vector2f(m_body.getPosition().x, m_body.getPosition().y + m_body.getRectangle().y / 2.f);
	Body groundBody = Body(groundRec, groundPos);

	Body& dbody = doodad.getBody();
	sf::Vector2f feetRec = sf::Vector2f(dbody.getRectangle().x, 0.f);
	sf::Vector2f feetPos = sf::Vector2f(dbody.getPosition().x, dbody.getPosition().y - dbody.getRectangle().y / 2.f);
	Body feetBody = Body(feetRec, feetPos);

	return groundBody.collide(feetBody);
}

bool Doodad::isDoodadOnLeft(Doodad& doodad)
{
	sf::Vector2f leftRec = sf::Vector2f(COLLISION_APPROXIMATION, m_body.getRectangle().y);
	sf::Vector2f leftPos = sf::Vector2f(m_body.getPosition().x - m_body.getRectangle().x / 2.f, m_body.getPosition().y);
	Body leftBody = Body(leftRec, leftPos);

    Body& dbody = doodad.getBody();
	sf::Vector2f feetRec = sf::Vector2f(0.f, dbody.getRectangle().y);
	sf::Vector2f feetPos = sf::Vector2f(dbody.getPosition().x + dbody.getRectangle().x / 2.f, dbody.getPosition().y);
	Body feetBody = Body(feetRec, feetPos);

	return leftBody.collide(feetBody);
}

void Doodad::collision(Doodad& doodad)
{
	if(m_body.collide(doodad.getBody()))
		collisionEvent(doodad);
}

EstheticEffect* Doodad::popEstheticEffect()
{
    if(m_aEstheticEffect.empty())
        return nullptr;

    EstheticEffect* ee = m_aEstheticEffect.at(0);
    m_aEstheticEffect.erase(m_aEstheticEffect.begin());
    return ee;
}

void Doodad::update(float dt)
{
	m_body.update(dt);
}
