//#include <SFML/Graphics/RectangleShape.hpp>
#include "EstheticEffectSmoke.h"
#include "tools.h"

EstheticEffectSmoke::EstheticEffectSmoke(float expirationTimer, float startSize, float endSize)
: EstheticEffect(expirationTimer)
, m_startSize(startSize)
, m_endSize(endSize)
{}

EstheticEffectSmoke::EstheticEffectSmoke()
: EstheticEffect()
, m_startSize(0.f)
, m_endSize(0.f)
{}

EstheticEffectSmoke::~EstheticEffectSmoke()
{}

void EstheticEffectSmoke::update(float dt)
{
    m_elaspedTime += dt;
    if(hasExpired())
        toDestroy(true);
    else
    {
        float timeElaspedRatio = m_elaspedTime / m_expirationTimer;
        float smokeSize = m_startSize + (m_endSize - m_startSize) * timeElaspedRatio;
        m_body.setRectangle(sf::Vector2f(smokeSize,smokeSize));
    }
}

void EstheticEffectSmoke::render(sf::RenderWindow& window)
{
    if(hasExpired())
        return;

    float timeElaspedRatio = m_elaspedTime / m_expirationTimer;

    sf::RectangleShape shape = getRectangleShapeForWindow(window, m_body.getRectangle(), m_body.getPosition());

    sf::Color color = m_color;
    color.a = 200 * (1 - timeElaspedRatio);
    shape.setFillColor(color);

    shape.setRotation(rand() % 90);

    window.draw(shape);
}
