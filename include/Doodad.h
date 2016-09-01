#ifndef DOODAD_H
#define DOODAD_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.h"
#include <BodyPhysic.h>
#include <EstheticEffect.h>

const float COLLISION_APPROXIMATION = 2.f;

class Visitor;

class Doodad : public Entity
{
    public:
        virtual ~Doodad(void);

        virtual BodyPhysic& getBody(void);
        virtual unsigned int getState(void);

        virtual void setBody(BodyPhysic body);
        virtual void setState(unsigned int state);
        virtual void setRectangle(sf::Vector2f rectangle);
        virtual void setPosition(sf::Vector2f position);

        virtual bool isBetweenBorder(float borderLeft, float borderRight, float borderBottom);

        virtual bool isDoodadOn(Doodad& doodad);
        virtual bool isDoodadOnLeft(Doodad& doodad);

        virtual void collision(Doodad& doodad);

        virtual void accept(Visitor& v);
        virtual void collisionEvent(Doodad& doodad);

        virtual void updateEE(float dt);
        virtual void renderEE(sf::RenderWindow& window);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        BodyPhysic m_body; //TODO
        unsigned int m_state;

        std::vector<EstheticEffect*> m_aEstheticEffect;

        Doodad(void);
};

#endif // DOODAD_H
