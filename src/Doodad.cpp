#include <math.h>

#include <Doodad.h>

Doodad::Doodad()
: m_state(0)
{}

Doodad::~Doodad()
{}

BodyPhysic& Doodad::getBody()
{
	return m_body;
}

unsigned int Doodad::getState()
{
	return m_state;
}

void Doodad::setBody(BodyPhysic body)
{
	m_body = body;
}

void Doodad::setState(unsigned int state)
{
	m_state = state;
}

void Doodad::setRectangle(sf::Vector2f rectangle)
{
    m_body.setRectangle(rectangle);
}

void Doodad::setPosition(sf::Vector2f position)
{
    m_body.setPosition(position);
}

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

void Doodad::accept(Visitor& v)
{}

void Doodad::collisionEvent(Doodad& doodad)
{}

void Doodad::updateEE(float dt)
{
    for(std::vector<EstheticEffect*>::iterator it = m_aEstheticEffect.begin(); it != m_aEstheticEffect.end(); )
    {
        (*it)->update(dt);
        if((*it)->isPendingDestruction())
        {
            EstheticEffect* ee = *it;
            m_aEstheticEffect.erase(it);
            delete ee;
        }
        else
            ++it;
    }
}

void Doodad::renderEE(sf::RenderWindow& window)
{
    for(std::vector<EstheticEffect*>::iterator it = m_aEstheticEffect.begin(); it != m_aEstheticEffect.end(); ++it)
        (*it)->render(window);
}

void Doodad::update(float dt)
{
	m_body.update(dt);
	updateEE(dt);
}

void Doodad::render(sf::RenderWindow& window)
{
    renderEE(window);
}
