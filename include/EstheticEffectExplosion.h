#ifndef ESTHETICEFFECTEXPLOSION_H
#define ESTHETICEFFECTEXPLOSION_H

#include "EstheticEffect.h"

class EstheticEffectExplosion : public EstheticEffect
{
    public:
        EstheticEffectExplosion(float expirationTimer, unsigned int layoutNumber);
        EstheticEffectExplosion(void);

        virtual ~EstheticEffectExplosion(void);

        //virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        //float m_explosionSize;
        unsigned int m_layoutNumber;

};

#endif // ESTHETICEFFECTEXPLOSION_H
