#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Body.h"

class Entity
{
    public:
        virtual ~Entity(void);

        virtual void toDestroy(bool destroy);
        virtual bool isPendingDestruction(void);

        virtual Body& getBody(void);
        virtual void setBody(Body body);
        virtual void setRectangle(sf::Vector2f rectangle);
        virtual void setPosition(sf::Vector2f position);
        virtual void setVelocity(sf::Vector2f velocity);
        virtual void setAngularVelocity(float angVel);

        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

    protected:
        bool m_pendingDestruction;
        Body m_body;

        Entity(void);
};

#endif // ENTITY_H
