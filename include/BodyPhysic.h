#ifndef BODYPHYSIC_H
#define BODYPHYSIC_H

#include "Body.h"

const float GRAVITY_VALUE = -200.f;

class BodyPhysic : public Body
{
    public:
        BodyPhysic(sf::Vector2f rec, sf::Vector2f pos);
        BodyPhysic();

        virtual ~BodyPhysic();

        virtual sf::Vector2f getVelocity();
        virtual float getAngle();
        virtual float getInvMass();
        virtual float getRestitution();

        virtual void setVelocity(sf::Vector2f vel);
        virtual void setAngle(float angle);
        virtual void setAngularVelocity(float angVel);
        virtual void setMass(float mass);
        virtual void setInvMass(float invMass);
        virtual void setFriction(float fri);
        virtual void setRestitution(float res);
        virtual void setGravity(bool gravity);

        virtual void update(float dt);

    protected:
        sf::Vector2f m_velocity;
        float m_angle, m_angularVelocity;

        float m_invMass;
        float m_friction, m_restitution;
        bool m_gravity;
};

#endif // BODYPHYSIC_H
