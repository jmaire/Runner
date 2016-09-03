#include "Entity.h"

Entity::Entity()
: m_pendingDestruction(false)
{}

Entity::~Entity()
{}

void Entity::toDestroy(bool destroy)
{
    m_pendingDestruction = destroy;
}

bool Entity::isPendingDestruction()
{
    return m_pendingDestruction;
}

Body& Entity::getBody()
{
	return m_body;
}

void Entity::setBody(Body body)
{
    m_body = body;
}

void Entity::setRectangle(sf::Vector2f rectangle)
{
    m_body.setRectangle(rectangle);
}

void Entity::setPosition(sf::Vector2f position)
{
    m_body.setPosition(position);
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    m_body.setVelocity(velocity);
}

void Entity::setAngularVelocity(float angVel)
{
    m_body.setAngularVelocity(angVel);
}

