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
    m_body.update(dt);
    m_elaspedTime += dt;
    if(hasExpired())
        toDestroy(true);

    float timeElaspedRatio = m_elaspedTime / m_expirationTimer;
    float smokeSize = m_startSize + (m_endSize - m_startSize) * timeElaspedRatio;
    m_body.setRectangle(sf::Vector2f(smokeSize, smokeSize));
}

void EstheticEffectSmoke::render(sf::RenderWindow& window)
{
    if(hasExpired())
        return;

    sf::RectangleShape shape = getRectangleShapeForWindow(window, m_body.getRectangle(), m_body.getPosition());

    float timeElaspedRatio = m_elaspedTime / m_expirationTimer;
    m_color.a = 150 * (1 - timeElaspedRatio);
    shape.setFillColor(m_color);

    shape.setRotation(rand() % 90);

    window.draw(shape);

}
