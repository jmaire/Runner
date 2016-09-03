#ifndef ESTHETICEFFECTDEBRIS_H
#define ESTHETICEFFECTDEBRIS_H

#include "EstheticEffect.h"

class EstheticEffectDebris : public EstheticEffect
{
    public:
        EstheticEffectDebris(float expirationTimer);
        EstheticEffectDebris(void);

        virtual ~EstheticEffectDebris();

        virtual void setColor(sf::Color color);

        //virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        sf::Color m_color;

};

#endif // ESTHETICEFFECTDEBRIS_H
