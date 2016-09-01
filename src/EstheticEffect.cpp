#include "EstheticEffect.h"

EstheticEffect::EstheticEffect(float expirationTimer)
: m_elaspedTime(0.f)
, m_expirationTimer(expirationTimer)
{}

EstheticEffect::EstheticEffect()
: EstheticEffect(0.f)
{}

EstheticEffect::~EstheticEffect()
{}

void EstheticEffect::setPosition(sf::Vector2f position)
{
    m_body.setPosition(position);
}

void EstheticEffect::setColor(sf::Color color)
{
    m_color = color;
}

void EstheticEffect::setGrayScale(unsigned int gs)
{
    m_color = sf::Color(gs,gs,gs);
}

bool EstheticEffect::hasExpired()
{
    return m_elaspedTime >= m_expirationTimer;
}

void EstheticEffect::update(float dt)
{
    m_elaspedTime += dt;
}

void EstheticEffect::render(sf::RenderWindow& window)
{}
