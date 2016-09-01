#include "EstheticEffectExplosion.h"
#include "tools.h"

EstheticEffectExplosion::EstheticEffectExplosion(float expirationTimer, float explosionSize, unsigned int layoutNumber)
: EstheticEffect(expirationTimer)
, m_explosionSize(explosionSize)
, m_layoutNumber(layoutNumber)
{}

EstheticEffectExplosion::EstheticEffectExplosion()
: EstheticEffectExplosion(0.f, 0.f, 1)
{}

EstheticEffectExplosion::~EstheticEffectExplosion()
{}

void EstheticEffectExplosion::render(sf::RenderWindow& window)
{
    float timeElaspedRatio = m_elaspedTime / m_expirationTimer;

    for(unsigned int i = 0; i < m_layoutNumber; i++)
    {
        float ratio = (float)i / m_layoutNumber;

        float layoutSize = m_explosionSize * (1.f - ratio);
        sf::Vector2f explosionRectangle = sf::Vector2f(layoutSize, layoutSize);
        sf::RectangleShape shape = getRectangleShapeForWindow(window, explosionRectangle, m_position);

        shape.setFillColor(sf::Color(255,
                                     150 * ratio + 105,
                                     50,
                                     200 * (1 - timeElaspedRatio))
                           );
        shape.setOrigin(getRectangleCenter(explosionRectangle));
        shape.setRotation(rand()%90);

        window.draw(shape);
    }
}
