#ifndef ROCKETLAUNCHER_H
#define ROCKETLAUNCHER_H

#include "Doodad.h"
#include "Rocket.h"

const float ROCKET_LAUNCHER_SIZE = 25.f;
const sf::Vector2f ROCKET_LAUNCHER_RECTANGLE = sf::Vector2f(ROCKET_LAUNCHER_SIZE, ROCKET_LAUNCHER_SIZE);
const sf::Color ROCKET_LAUNCHER_COLOR = sf::Color(120, 120, 120, 255);
const float ROCKET_LAUNCHER_WEAPON_LENGHT = 25.f;
const sf::Vector2f ROCKET_LAUNCHER_WEAPON_RECTANGLE = sf::Vector2f(ROCKET_LAUNCHER_WEAPON_LENGHT, 15.f);
const sf::Color ROCKET_LAUNCHER_WEAPON_COLOR = sf::Color(180, 180, 180, 255);

const float ROCKET_LAUNCHER_FIRE_COOLDOWN = 2.f;

class RocketLauncher : public Doodad
{
    public:
        RocketLauncher(void);
        RocketLauncher(sf::Vector2f pos);

        virtual ~RocketLauncher(void);

        void setTarget(Doodad* target);

        void launchRocket(void);

        Rocket* popRocket(void);

        void update(float dt);
        void render(sf::RenderWindow& window);

    protected:
        Doodad *m_target;
        float m_fireCooldown;

        std::vector<Rocket*> m_rocketList;
};

#endif // ROCKETLAUNCHER_H
