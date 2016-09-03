#ifndef BODY_H
#define BODY_H

#include <math.h>

#include <SFML/System/Vector2.hpp>

class Body
{
    public:
        Body(void);
        Body(sf::Vector2f rec, sf::Vector2f pos);

        virtual ~Body(void);

        virtual sf::Vector2f getRectangle(void);
        virtual sf::Vector2f getPosition(void);
        virtual float getXMin(void);
        virtual float getXMax(void);
        virtual float getYMin(void);
        virtual float getYMax(void);

        virtual void setRectangle(sf::Vector2f rec);
        virtual void setPosition(sf::Vector2f pos);

        virtual bool collide(Body& body);

        virtual void update(float dt);

    protected:
        sf::Vector2f m_rectangle;
        sf::Vector2f m_position;

};

#endif // BODY_H
