#ifndef BACKGROUNDMOON_H
#define BACKGROUNDMOON_H

#include "BackgroundDoodad.h"

const float BACKGROUND_MOON_GLOWING_DURATION = 2.f;
const float BACKGROUND_MOON_GLOWING_BONUS_SIZE = 10.f;
const sf::Color BACKGROUND_MOON_COLOR = sf::Color(200, 200, 50);

class BackgroundMoon : public BackgroundDoodad
{
    public:
        BackgroundMoon(void);
        virtual ~BackgroundMoon(void);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        float m_glowingTimer;
};

#endif // BACKGROUNDMOON_H
