#include "BodyPhysic.h"

BodyPhysic::BodyPhysic(sf::Vector2f rec, sf::Vector2f pos)
: Body(rec, pos)
, m_angle(0.f)
, m_angularVelocity(0.f)
, m_invMass(0.f)
, m_friction(0.f)
, m_restitution(0.f)
, m_gravity(false)
{}

BodyPhysic::BodyPhysic()
: BodyPhysic(sf::Vector2f(),sf::Vector2f())
{}

BodyPhysic::~BodyPhysic()
{}

sf::Vector2f BodyPhysic::getVelocity()
{
	return m_velocity;
}

float BodyPhysic::getAngle()
{
    return m_angle;
}

float BodyPhysic::getInvMass()
{
	return m_invMass;
}

float BodyPhysic::getRestitution()
{
	return m_restitution;
}

void BodyPhysic::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

void BodyPhysic::setAngle(float angle)
{
    m_angle = angle;
}

void BodyPhysic::setAngularVelocity(float angVel)
{
    m_angularVelocity = angVel;
}

void BodyPhysic::setMass(float mass)
{
    if(0.f == mass)
        m_invMass = 0.f;
    else
        m_invMass = 1.f / mass;
}

void BodyPhysic::setInvMass(float invMass)
{
    m_invMass = invMass;
}

void BodyPhysic::setFriction(float fri)
{
    m_friction = fri;
}

void BodyPhysic::setRestitution(float res)
{
    m_restitution = res;
}

void BodyPhysic::setGravity(bool gravity)
{
	m_gravity = gravity;
}

void BodyPhysic::update(float dt)
{
	m_velocity *= (float)pow(1.f - m_friction, dt);
	if(0 != m_gravity)
	{
		m_velocity.y += GRAVITY_VALUE * dt;
	}

	m_position += m_velocity * dt;
	m_angle += fmod(m_angularVelocity * dt, 360.f);
}
