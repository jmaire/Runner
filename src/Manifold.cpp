#include "Manifold.h"

#include "tools.h"

Manifold::Manifold()
{}

Manifold::Manifold(BodyPhysic& body1, BodyPhysic& body2)
: m_body1(&body1)
, m_body2(&body2)
{
    computeManifold();
}

Manifold::~Manifold()
{}

void Manifold::computeManifold()
{
	float xMin = MY_MAX(m_body1->getXMin(), m_body2->getXMin());
	float xMax = MY_MIN(m_body1->getXMax(), m_body2->getXMax());
	float xLength = xMax - xMin;

	float yMin = MY_MAX(m_body1->getYMin(), m_body2->getYMin());
	float yMax = MY_MIN(m_body1->getYMax(), m_body2->getYMax());
	float yLength = yMax - yMin;

	if(xLength <= 0.f || yLength <= 0.f)
		return;

	sf::Vector2f p1 = m_body1->getPosition();
	sf::Vector2f p2 = m_body2->getPosition();

	if(xLength < yLength)
	{
	    m_penetration = xLength;
		if(p2.x - p1.x < 0.f)
		{
			m_normal = sf::Vector2f(-1.f, 0.f);
		}
		else
		{
			m_normal = sf::Vector2f(1.f, 0.f);
		}
	}
	else
	{
        m_penetration = yLength;
		if(p2.y - p1.y < 0.f)
		{
			m_normal = sf::Vector2f(0.f, -1.f);
		}
		else
		{
			m_normal = sf::Vector2f(0.f, 1.f);
		}
	}
}

void Manifold::applyImpulse()
{
	sf::Vector2f rv = m_body2->getVelocity() - m_body1->getVelocity();

	float velAlongNormal = rv.x * m_normal.x + rv.y * m_normal.y;
	if(velAlongNormal > 0.f)
		return;

	float e = MY_MIN(m_body1->getRestitution(), m_body2->getRestitution());
	float j = -(1.f + e) * velAlongNormal;

	float invMass1 = m_body1->getInvMass();
	float invMass2 = m_body2->getInvMass();
	float invMassSum = invMass1 + invMass2;

	if(0.f != invMassSum)
		j /= invMassSum;

	sf::Vector2f impulse = m_normal * j;

	sf::Vector2f vel1 = m_body1->getVelocity() - (impulse * invMass1);
	m_body1->setVelocity(vel1);

	sf::Vector2f vel2 = m_body2->getVelocity() + (impulse * invMass2);
	m_body2->setVelocity(vel2);
}

void Manifold::positionalCorrection()
{
	float correctionValue = m_penetration * CORRECTION_PERCENT;
	sf::Vector2f correctionVector = m_normal;
	correctionVector *= correctionValue;

	float invMass1 = m_body1->getInvMass();
	float invMass2 = m_body2->getInvMass();
	float invMassSum = invMass1 + invMass2;

	if(0.f != invMassSum)
		correctionVector /= invMassSum;

	sf::Vector2f correctionVector1 = correctionVector * invMass1;
	sf::Vector2f correctionVector2 = correctionVector * invMass2;

	sf::Vector2f p1 = m_body1->getPosition() - correctionVector1;
  	m_body1->setPosition(p1);

	sf::Vector2f p2 = m_body2->getPosition() + correctionVector2;
  	m_body2->setPosition(p2);
}
