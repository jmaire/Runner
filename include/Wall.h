#ifndef WALL_H
#define WALL_H

#include "VisitorWall.h"

const sf::Color WALL_INDESTRUCTIBLE_COLOR = sf::Color(100, 50, 10, 255);
const sf::Color WALL_DESTRUCTIBLE_COLOR = sf::Color(200, 150, 50, 255);
const float WALL_DEBRIS_SIZE = 10.f;

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
        virtual void collisionEvent(Doodad& doodad);

        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_isDestructible, m_isDestroyed;
};

#endif // WALL_H
