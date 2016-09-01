#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/RenderWindow.hpp>

class Entity
{
    public:
        virtual ~Entity(void);

        virtual void toDestroy(bool destroy);
        virtual bool isPendingDestruction(void);

        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

    protected:
        bool m_pendingDestruction;

        Entity(void);
};

#endif // ENTITY_H
