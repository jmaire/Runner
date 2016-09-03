#ifndef WALL_H
#define WALL_H

#include "Doodad.h"
//#include "VisitorWall.h"

const sf::Color WALL_INDESTRUCTIBLE_COLOR = sf::Color(95, 75, 60, 255);
const sf::Color WALL_DESTRUCTIBLE_COLOR = sf::Color(255, 200, 100, 255);
const float WALL_DEBRIS_DURATION = 7.f;
const float WALL_DEBRIS_SIZE = 8.f;

class Wall : public Doodad
{
    public:
        Wall(void);
        Wall(sf::Vector2f rec, sf::Vector2f pos);

        virtual ~Wall(void);

        virtual void setDestructible(bool isDes);
        virtual bool isDestructible(void);

        virtual void createDebris(void);

        virtual void accept(Visitor& v);

        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_isDestructible, m_isDestroyed;
};

#endif // WALL_H
