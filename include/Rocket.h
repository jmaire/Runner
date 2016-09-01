#ifndef ROCKET_H
#define ROCKET_H

#include "EstheticEffectSmoke.h"
#include "VisitorRocket.h"

const float ROCKET_DURATION = 3.f;
const float ROCKET_MASS = 1.f;
const float ROCKET_SIZE = 12.f;
const sf::Vector2f ROCKET_RECTANGLE = sf::Vector2f(ROCKET_SIZE*1.5f, ROCKET_SIZE);
const float ROCKET_VELOCITY = 800.f;
const float ROCKET_FRICTION = 0.01f;
const sf::Color ROCKET_COLOR = sf::Color(100, 150, 50, 255);

const float ROCKET_EXPLOSION_TIME = 0.5f;
const float ROCKET_EXPLOSION_SIZE = 60.f;
const sf::Vector2f ROCKET_EXPLOSION_RECTANGLE = sf::Vector2f(ROCKET_EXPLOSION_SIZE, ROCKET_EXPLOSION_SIZE);
const float ROCKET_EXPLOSION_VELOCITY = 200.f;

const float ROCKET_SMOKE_DURATION = 0.4f;
const float ROCKET_SMOKE_STARTING_SIZE = 12.f;
const float ROCKET_SMOKE_END_SIZE = 36.f;
const sf::Color ROCKET_SMOKE_COLOR = sf::Color(150, 150, 150);

class Rocket : public Doodad
{
    public:
        Rocket(void);
        Rocket(sf::Vector2f pos, sf::Vector2f vel);

        virtual ~Rocket(void);

        virtual void explode(void);
        virtual bool isExploding(void);

        virtual void propelledCharacter(void);
        virtual bool hadPropelledCharacter(void);

        virtual void createSmoke(void);

        virtual void accept(Visitor& v);
        virtual void collisionEvent(Doodad& doodad);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_isExploding, m_propelledCharacter;
        float m_rocketTimer, m_explosionTimer;

        float m_smokeTimer;
};

#endif // ROCKET_H
