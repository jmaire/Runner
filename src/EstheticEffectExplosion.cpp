#include "EstheticEffectExplosion.h"
#include "tools.h"

EstheticEffectExplosion::EstheticEffectExplosion(float expirationTimer, unsigned int layoutNumber)
: EstheticEffect(expirationTimer)
, m_layoutNumber(layoutNumber)
{}

EstheticEffectExplosion::EstheticEffectExplosion()
: EstheticEffectExplosion(0.f, 1)
{}

EstheticEffectExplosion::~EstheticEffectExplosion()
{}

void EstheticEffectExplosion::render(sf::RenderWindow& window)
{
    float timeElaspedRatio = m_elaspedTime / m_expirationTimer;

    for(unsigned int i = 0; i < m_layoutNumber; i++)
    {
        float ratio = (float)i / m_layoutNumber;

        sf::Vector2f explosionRectangle = m_body.getRectangle() * (1.f - ratio);
        sf::RectangleShape shape = getRectangleShapeForWindow(window, explosionRectangle, m_body.getPosition());

        shape.setFillColor(sf::Color(255,
                                     150 * ratio + 105,
                                     50,
                                     200 * (1.f - timeElaspedRatio))
                           );
        shape.setOrigin(getRectangleCenter(explosionRectangle));
        shape.setRotation(rand()%90);

        window.draw(shape);
    }
}
