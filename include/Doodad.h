#ifndef DOODAD_H
#define DOODAD_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.h"
#include "EstheticEffect.h"

const float COLLISION_APPROXIMATION = 2.f;

class Visitor;

class Doodad : public Entity
{
    public:
        virtual ~Doodad(void);

        virtual bool isBetweenBorder(float borderLeft, float borderRight, float borderBottom);

        virtual bool isDoodadOn(Doodad& doodad);
        virtual bool isDoodadOnLeft(Doodad& doodad);

        virtual void collision(Doodad& doodad);

        virtual void accept(Visitor& v) {};
        virtual void collisionEvent(Doodad& doodad) {};

        virtual EstheticEffect* popEstheticEffect(void);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window) {};

    protected:
        std::vector<EstheticEffect*> m_aEstheticEffect;

        Doodad(void);
};

#endif // DOODAD_H
