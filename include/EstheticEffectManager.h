#ifndef ESTHETICEFFECTMANAGER_H
#define ESTHETICEFFECTMANAGER_H

#include "EstheticEffect.h"

class EstheticEffectManager
{
    public:
        virtual ~EstheticEffectManager(void);

        static void clear(void);

        static void insertEstheticEffect(EstheticEffect* ee);

        static void update(float dt);
        static void render(sf::RenderWindow& window);

    protected:
        static std::vector<EstheticEffect*> m_aEstheticEffect;

    private:
        EstheticEffectManager(void);
};

#endif // ESTHETICEFFECTMANAGER_H
