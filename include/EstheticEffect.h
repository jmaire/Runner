#ifndef ESTHETICEFFECT_H
#define ESTHETICEFFECT_H

#include "Entity.h"

class EstheticEffect : public Entity
{
    public:
        EstheticEffect(float expirationTimer);
        EstheticEffect(void);

        virtual ~EstheticEffect(void);

        virtual bool hasExpired(void);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        float m_elaspedTime, m_expirationTimer;

};

#endif // ESTHETICEFFECT_H
