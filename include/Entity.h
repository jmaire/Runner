#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "BodyPhysic.h"

class Entity
{
    public:
        virtual ~Entity(void);

        virtual void toDestroy(bool destroy);
        virtual bool isPendingDestruction(void);

        virtual BodyPhysic& getBody(void);
        virtual void setBody(BodyPhysic body);
        virtual void setRectangle(sf::Vector2f rectangle);
        virtual void setPosition(sf::Vector2f position);
        virtual void setVelocity(sf::Vector2f velocity);
        virtual void setAngularVelocity(float angVel);

        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

    protected:
        bool m_pendingDestruction;
        BodyPhysic m_body;

        Entity(void);
};

#endif // ENTITY_H
