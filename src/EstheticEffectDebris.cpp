#include "EstheticEffectDebris.h"
#include "tools.h"
#include "Wall.h"

EstheticEffectDebris::EstheticEffectDebris(float expirationTimer)
: EstheticEffect(expirationTimer)
{
    m_body.setGravity(true);
}

EstheticEffectDebris::EstheticEffectDebris()
: EstheticEffectDebris(0.f)
{}

EstheticEffectDebris::~EstheticEffectDebris()
{}

void EstheticEffectDebris::setColor(sf::Color color)
{
    m_color = color;
}

void EstheticEffectDebris::render(sf::RenderWindow& window)
{
    sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();

    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);
    shape.setRotation(m_body.getAngle());

    m_color.a = 255 * (1 -  (float)(m_elaspedTime / m_expirationTimer));
    shape.setFillColor(m_color);

	window.draw(shape);
}
