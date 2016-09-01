#ifndef WALL_H
#define WALL_H

#include "VisitorWall.h"

const sf::Color WALL_INDESTRUCTIBLE_COLOR = sf::Color(0, 255, 0, 255);
const sf::Color WALL_DESTRUCTIBLE_COLOR = sf::Color(0, 255, 255, 255);

class Wall : public Doodad
{
    public:
        Wall();
        Wall(sf::Vector2f rec, sf::Vector2f pos);

        virtual ~Wall();

        void setDestructible(bool isDes);
        bool isDestructible();

        virtual void accept(Visitor& v);
        virtual void collisionEvent(Doodad& doodad);

        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_isDestructible, m_isDestroyed;
};

#endif // WALL_H
