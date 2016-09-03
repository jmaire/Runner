#ifndef ESTHETICEFFECTSMOKE_H
#define ESTHETICEFFECTSMOKE_H

#include "EstheticEffect.h"

class EstheticEffectSmoke : public EstheticEffect
{
    public:
        EstheticEffectSmoke(float expirationTimer, float startSize, float endSize);
        EstheticEffectSmoke(void);

        virtual ~EstheticEffectSmoke(void);

        virtual void setColor(sf::Color color);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        float m_startSize, m_endSize;
        sf::Vector2f m_velocity;
        sf::Color m_color;

    private:
};

#endif // ESTHETICEFFECTSMOKE_H
