#ifndef ESTHETICEFFECT_H
#define ESTHETICEFFECT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Body.h"
#include "Entity.h"

class EstheticEffect : public Entity
{
    public:
        EstheticEffect(float expirationTimer);
        EstheticEffect();

        virtual ~EstheticEffect();

        virtual bool hasExpired();

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        float m_elaspedTime, m_expirationTimer;

};

#endif // ESTHETICEFFECT_H
