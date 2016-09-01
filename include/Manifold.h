#ifndef MANIFOLD_H
#define MANIFOLD_H

#include <BodyPhysic.h>

const float CORRECTION_PERCENT = 1.f;

class Manifold
{
    public:
        Manifold();
        Manifold(BodyPhysic& body1, BodyPhysic& body2);

        ~Manifold();

        void computeManifold();
        void applyImpulse();
        void positionalCorrection();

    private:
        BodyPhysic *m_body1, *m_body2;
        float m_penetration;
        sf::Vector2f m_normal;
};

#endif // MANIFOLD_H