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

bool EstheticEffect::hasExpired()
{
    return m_elaspedTime >= m_expirationTimer;
}

void EstheticEffect::update(float dt)
{
    m_body.update(dt);
    m_elaspedTime += dt;
}

void EstheticEffect::render(sf::RenderWindow& window)
{}
