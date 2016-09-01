#ifndef ESTHETICEFFECT_H
#define ESTHETICEFFECT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Body.h"
#include "Entity.h"

class EstheticEffect : public Entity
{
    public:
        EstheticEffect(float expirationTimer);
        EstheticEffect();

        virtual ~EstheticEffect();

        virtual void setPosition(sf::Vector2f position);
        virtual void setColor(sf::Color color);
        virtual void setGrayScale(unsigned int gs);

        virtual bool hasExpired();

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        Body m_body;
        float m_elaspedTime, m_expirationTimer;
        sf::Color m_color;

    private:
};

#endif // ESTHETICEFFECT_H
