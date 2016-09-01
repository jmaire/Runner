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
