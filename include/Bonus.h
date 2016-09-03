#ifndef BONUS_H
#define BONUS_H

#include "Doodad.h"
//#include "VisitorBonus.h"

const float BONUS_SIZE = 15.f;
const float BONUS_ANGULAR_VELOCITY = 120.f;
const float BONUS_GLOWING_DURATION = 1.f;
const float BONUS_GLOWING_MAX_SIZE = BONUS_SIZE * 2.f;
const sf::Vector2f BONUS_RECTANGLE = sf::Vector2f(BONUS_SIZE, BONUS_SIZE);
const sf::Color BONUS_COLOR = sf::Color(255, 0, 255, 255);
const sf::Color BONUS_GLOWING_COLOR = sf::Color(255, 100, 255);

class Bonus : public Doodad
{
    public:
        Bonus(void);
        Bonus(sf::Vector2f pos);

        virtual ~Bonus(void);

        virtual bool isTaken(void);
        virtual void setTaken(bool taken);

        virtual void accept(Visitor& v);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_isTaken;
        float m_glowingTimer;
};

#endif // BONUS_H
