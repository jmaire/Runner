#ifndef ROCKET_H
#define ROCKET_H

#include "VisitorRocket.h"

// COMMON
const float ROCKET_DURATION = 3.f;
const float ROCKET_MASS = 1.f;
const float ROCKET_SIZE = 12.f;
const sf::Vector2f ROCKET_RECTANGLE = sf::Vector2f(ROCKET_SIZE*1.5f, ROCKET_SIZE);
const float ROCKET_VELOCITY = 800.f;
const float ROCKET_FRICTION = 0.01f;
const sf::Color ROCKET_COLOR = sf::Color(90, 125, 90, 255);

const float ROCKET_EXPLOSION_SIZE = 60.f;
const sf::Vector2f ROCKET_EXPLOSION_RECTANGLE = sf::Vector2f(ROCKET_EXPLOSION_SIZE, ROCKET_EXPLOSION_SIZE);
const float ROCKET_EXPLOSION_VELOCITY = 200.f;
const float ROCKET_EXPLOSION_DURATION = 0.5f;
const unsigned int ROCKET_EXPLOSION_LAYOUT = 6;

const float ROCKET_SMOKE_DURATION = 0.2f;
const float ROCKET_SMOKE_STARTING_SIZE = 12.f;
const float ROCKET_SMOKE_END_SIZE = 36.f;
const sf::Color ROCKET_SMOKE_COLOR = sf::Color(150, 150, 150);

// CHARACTER


// ROCKET LAUNCHER
const float ROCKET_BASE_ACCELERATION = 1000.f;
const float ROCKET_BONUS_ACCELERATION = 3000.f;

class Rocket : public Doodad
{
    public:
        Rocket(void);
        Rocket(sf::Vector2f pos, sf::Vector2f vel);

        virtual ~Rocket(void);

        void setTarget(Doodad* target);

        virtual void explode(void);
        virtual bool isExploding(void);

        virtual void propelledCharacter(void);
        virtual bool hadPropelledCharacter(void);

        virtual bool propelHorizontally(void);
        virtual void setPropelHorizontally(bool propel);

        virtual void createSmoke(void);
        virtual void createExplosion(void);

        virtual void accept(Visitor& v);
        virtual void collisionEvent(Doodad& doodad);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_isExploding, m_isDone, m_propelledCharacter, m_propelHorizontally;
        float m_rocketTimer;

        float m_smokeTimer;
        Doodad *m_target;
};

#endif // ROCKET_H
