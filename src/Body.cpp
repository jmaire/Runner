#include <stdio.h>

#include <Body.h>

const float CORRECTION_PERCENT = 0.2f;
const float SLOP = 0.2f;

Body::Body()
: m_rectangle(sf::Vector2f())
, m_position(sf::Vector2f())
{}

Body::Body(sf::Vector2f rec, sf::Vector2f pos)
: m_rectangle(rec)
, m_position(pos)
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

void Body::setRectangle(sf::Vector2f rec)
{
	m_rectangle = rec;
}

void Body::setPosition(sf::Vector2f rec)
{
	m_position = rec;
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
{}
