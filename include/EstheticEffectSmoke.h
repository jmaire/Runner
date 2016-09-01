#ifndef ESTHETICEFFECTSMOKE_H
#define ESTHETICEFFECTSMOKE_H

#include "EstheticEffect.h"

class EstheticEffectSmoke : public EstheticEffect
{
    public:
        EstheticEffectSmoke(float expirationTimer, float startSize, float endSize);
        EstheticEffectSmoke();

        virtual ~EstheticEffectSmoke();

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        float m_startSize, m_endSize;

    private:
};

#endif // ESTHETICEFFECTSMOKE_H
