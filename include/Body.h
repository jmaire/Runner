#ifndef BODY_H
#define BODY_H

#include <SFML/System/Vector2.hpp>

const float GRAVITY_VALUE = -200.f;

class Body
{
    public:
        Body(sf::Vector2f rec, sf::Vector2f pos);
        Body(void);

        virtual ~Body(void);

        virtual sf::Vector2f getRectangle(void);
        virtual sf::Vector2f getPosition(void);
        virtual float getXMin(void);
        virtual float getXMax(void);
        virtual float getYMin(void);
        virtual float getYMax(void);
        virtual sf::Vector2f getVelocity(void);
        virtual float getAngle(void);
        virtual float getInvMass(void);
        virtual float getRestitution(void);

        virtual void setRectangle(sf::Vector2f rec);
        virtual void setPosition(sf::Vector2f pos);
        virtual void setVelocity(sf::Vector2f vel);
        virtual void setAcceleration(sf::Vector2f acc);
        virtual void setAngle(float angle);
        virtual void setAngularVelocity(float angVel);
        virtual void setMass(float mass);
        virtual void setInvMass(float invMass);
        virtual void setFriction(float fri);
        virtual void setRestitution(float res);
        virtual void setGravity(bool gravity);

        virtual void useVelocityLimit(bool useVelocityLimit);
        virtual void setVelocityLimit(float velocityLimit);

        virtual bool collide(Body& body);

        virtual void update(float dt);

    protected:
        sf::Vector2f m_rectangle, m_position, m_velocity, m_acceleration;
        float m_angle, m_angularVelocity;

        float m_invMass;
        float m_friction, m_restitution;
        bool m_gravity;

        float m_velocityLimit;
        bool m_useVelocityLimit;
};

#endif // BODY_H
