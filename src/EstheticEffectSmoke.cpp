//#include <SFML/Graphics/RectangleShape.hpp>
#include "EstheticEffectSmoke.h"
#include "tools.h"

EstheticEffectSmoke::EstheticEffectSmoke(float expirationTimer, float startSize, float endSize)
: EstheticEffect(expirationTimer)
, m_startSize(startSize)
, m_endSize(endSize)
{}

EstheticEffectSmoke::EstheticEffectSmoke()
: EstheticEffectSmoke(0.f, 0.f, 0.f)
{}

EstheticEffectSmoke::~EstheticEffectSmoke()
{}

void EstheticEffectSmoke::setColor(sf::Color color)
{
    m_color = color;
}

void EstheticEffectSmoke::update(float dt)
{
    m_elaspedTime += dt;
    if(hasExpired())
        toDestroy(true);
    else
    {
        float timeElaspedRatio = m_elaspedTime / m_expirationTimer;
        m_size = m_startSize + (m_endSize - m_startSize) * timeElaspedRatio;
    }
}

void EstheticEffectSmoke::render(sf::RenderWindow& window)
{
    if(hasExpired())
        return;

    float timeElaspedRatio = m_elaspedTime / m_expirationTimer;

    sf::RectangleShape shape = getRectangleShapeForWindow(window, sf::Vector2f(m_size,m_size), m_position);

    m_color.a = 200 * (1 - timeElaspedRatio);
    shape.setFillColor(m_color);

    shape.setRotation(rand() % 90);

    window.draw(shape);

}
