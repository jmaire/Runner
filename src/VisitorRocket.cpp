#include "VisitorRocket.h"
#include "tools.h"

VisitorRocket::VisitorRocket(Rocket* rocket)
: VisitorDoodad<Rocket>(rocket)
{}

VisitorRocket::VisitorRocket()
: VisitorRocket(nullptr)
{}

VisitorRocket::~VisitorRocket()
{}

void VisitorRocket::visitCharacter(Character* e)
{
    if(!m_doodad->isExploding() || m_doodad->hadPropelledCharacter())
        return;

    m_doodad->propelledCharacter();

	sf::Vector2f dPos = e->getBody().getPosition();
	sf::Vector2f gPos = m_doodad->getBody().getPosition();
	float deltaX = dPos.x - gPos.x;
	float deltaY = dPos.y - gPos.y;

	float explodeValue = ROCKET_EXPLOSION_VELOCITY;
	if(fabs(deltaX) > fabs(deltaY))
		explodeValue /= 2.f;

	sf::Vector2f explodeVelocity;
	if(deltaY>0.f)
		explodeVelocity = sf::Vector2f(0.f, explodeValue);
	else
		explodeVelocity = sf::Vector2f(0.f, -explodeValue);

	Body& body = e->getBody();
	e->getBody().setVelocity(body.getVelocity() + explodeVelocity);
}

void VisitorRocket::visitWall(Wall* e)
{
    if(m_doodad->isExploding())
    {
        if(e->isDestructible())
        {
            e->toDestroy(true);
            e->createDebris();
        }
    }
    else
        m_doodad->explode();
}

