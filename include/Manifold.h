#ifndef MANIFOLD_H
#define MANIFOLD_H

#include <Body.h>

const float CORRECTION_PERCENT = 1.f;

class Manifold
{
    public:
        Manifold(void);
        Manifold(Body& body1, Body& body2);

        virtual ~Manifold(void);

        void computeManifold(void);
        void applyImpulse(void);
        void positionalCorrection(void);

    private:
        Body *m_body1, *m_body2;
        float m_penetration;
        sf::Vector2f m_normal;
};

#endif // MANIFOLD_H
