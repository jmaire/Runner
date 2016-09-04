#include <cmath>
#include "Body.h"

Body::Body(sf::Vector2f rec, sf::Vector2f pos)
: m_rectangle(rec)
, m_position(pos)
, m_angle(0.f)
, m_angularVelocity(0.f)
, m_invMass(0.f)
, m_friction(0.f)
, m_restitution(0.f)
, m_gravity(false)
, m_velocityLimit(0.f)
, m_useVelocityLimit(false)
{}

Body::Body()
: Body(sf::Vector2f(),sf::Vector2f())
{}

Body::~Body()
{}

sf::Vector2f Body::getRectangle()
{
	return m_rectangle;
}

sf::Vector2f Body::getPosition()
{
	return m_position;
}

float Body::getXMin()
{
	return m_position.x - m_rectangle.x / 2.f;
}

float Body::getXMax()
{
	return m_position.x + m_rectangle.x / 2.f;
}

float Body::getYMin()
{
	return m_position.y - m_rectangle.y / 2.f;
}

float Body::getYMax()
{
	return m_position.y + m_rectangle.y / 2.f;
}

sf::Vector2f Body::getVelocity()
{
	return m_velocity;
}

float Body::getAngle()
{
    return m_angle;
}

float Body::getInvMass()
{
	return m_invMass;
}

float Body::getRestitution()
{
	return m_restitution;
}

void Body::setRectangle(sf::Vector2f rec)
{
	m_rectangle = rec;
}

void Body::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void Body::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

void Body::setAcceleration(sf::Vector2f acc)
{
    m_acceleration = acc;
}

void Body::setAngle(float angle)
{
    m_angle = angle;
}

void Body::setAngularVelocity(float angVel)
{
    m_angularVelocity = angVel;
}

void Body::setMass(float mass)
{
    if(0.f == mass)
        m_invMass = 0.f;
    else
        m_invMass = 1.f / mass;
}

void Body::setInvMass(float invMass)
{
    m_invMass = invMass;
}

void Body::setFriction(float fri)
{
    m_friction = fri;
}

void Body::setRestitution(float res)
{
    m_restitution = res;
}

void Body::setGravity(bool gravity)
{
	m_gravity = gravity;
}

void Body::useVelocityLimit(bool useVelocityLimit)
{
    m_useVelocityLimit = useVelocityLimit;
}

void Body::setVelocityLimit(float velocityLimit)
{
    m_velocityLimit = velocityLimit;
    m_useVelocityLimit = true;
}

bool Body::collide(Body& body)
{
	if(getXMax() < body.getXMin()
        || getXMin() > body.getXMax())
		return false;

	if(getYMax() < body.getYMin()
        || getYMin() > body.getYMax())
		return false;

	return true;
}

void Body::update(float dt)
{
	if(m_gravity)
		m_velocity.y += GRAVITY_VALUE * dt;

    m_velocity += m_acceleration * dt;
	m_velocity *= (float)pow(1.f - m_friction, dt);

    if(m_useVelocityLimit)
    {
        float velocityValue = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        if(velocityValue > m_velocityLimit)
            m_velocity *= (m_velocityLimit / velocityValue);
    }

	m_position += m_velocity * dt;
	m_angle += fmod(m_angularVelocity * dt, 360.f);
}
