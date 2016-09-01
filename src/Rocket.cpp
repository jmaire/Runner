#include <cmath>
#include "EstheticEffectExplosion.h"
#include "EstheticEffectSmoke.h"
#include "Rocket.h"
#include "tools.h"

Rocket::Rocket()
: Doodad()
, m_isExploding(false)
, m_isDone(false)
, m_propelledCharacter(false)
, m_rocketTimer(0.f)
//, m_explosionTimer(0.f)
, m_smokeTimer(0.f)
{
    m_body.setRectangle(ROCKET_RECTANGLE);
    m_body.setMass(ROCKET_MASS);
    m_body.setFriction(ROCKET_FRICTION);
    m_body.setGravity(true);
}

Rocket::Rocket(sf::Vector2f pos, sf::Vector2f vel)
: Rocket()
{
    m_body.setPosition(pos);
    m_body.setVelocity(vel);
}

Rocket::~Rocket()
{}

void Rocket::explode()
{
    m_isExploding = true;
    m_body.setGravity(false);
    m_body.setMass(0.f);
    m_body.setFriction(0.f);
    m_body.setRestitution(0.f);
    m_body.setVelocity(sf::Vector2f(0.f,0.f));
    m_body.setRectangle(ROCKET_EXPLOSION_RECTANGLE);
    createExplosion();
}

bool Rocket::isExploding()
{
    return m_isExploding;
}

void Rocket::propelledCharacter()
{
    m_propelledCharacter = true;
}

bool Rocket::hadPropelledCharacter()
{
    return m_propelledCharacter;
}

void Rocket::createSmoke()
{
    EstheticEffectSmoke* ees = new EstheticEffectSmoke(ROCKET_SMOKE_DURATION, ROCKET_SMOKE_STARTING_SIZE, ROCKET_SMOKE_END_SIZE);
    ees->setPosition(m_body.getPosition());
    ees->setColor(ROCKET_SMOKE_COLOR);
    m_aEstheticEffect.push_back(ees);
}

void Rocket::createExplosion()
{
    EstheticEffectExplosion* eee = new EstheticEffectExplosion(ROCKET_EXPLOSION_DURATION, ROCKET_EXPLOSION_SIZE, ROCKET_EXPLOSION_LAYOUT);
    eee->setPosition(m_body.getPosition());
    m_aEstheticEffect.push_back(eee);
}

void Rocket::accept(Visitor& v)
{
	v.visitRocket(this);
}

void Rocket::collisionEvent(Doodad& doodad)
{
	VisitorRocket v = VisitorRocket(this);
	doodad.accept(v);
}

void Rocket::update(float dt)
{
    m_body.update(dt);

    if(m_isExploding)
    {
        if(m_isDone || hadPropelledCharacter())
            toDestroy(true);

        m_isDone = true;
    }
    else
    {
        m_rocketTimer += dt;
        if(m_rocketTimer >= ROCKET_DURATION)
            explode();

        m_smokeTimer += dt;
        if(m_smokeTimer > 0.02f)
        {
            m_smokeTimer = 0.f;
            createSmoke();
        }
    }

}

void Rocket::render(sf::RenderWindow& window)
{
	sf::Vector2f rectangle = m_body.getRectangle();
	sf::Vector2f position = m_body.getPosition();

    if(!m_isExploding)
    {
        sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);

        shape.setFillColor(ROCKET_COLOR);

        sf::Vector2f velocity = m_body.getVelocity();
        float angle = atan2(velocity.y, velocity.x) * 180.f / M_PI;
        shape.setRotation(-angle);

        window.draw(shape);
    }
}
