#include "Bonus.h"
#include "EstheticEffectSmoke.h"
#include "tools.h"

Bonus::Bonus()
: Doodad()
, m_isTaken(false)
, m_glowingTimer(0.f)
{
    m_body.setRectangle(BONUS_RECTANGLE);
    m_body.setAngle(rand() % 90);
    m_body.setAngularVelocity(BONUS_ANGULAR_VELOCITY);
}

Bonus::Bonus(sf::Vector2f pos)
: Bonus()
{
    m_body.setPosition(pos);
}

Bonus::~Bonus()
{}

bool Bonus::isTaken(void)
{
    return m_isTaken;
}

void Bonus::setTaken(bool taken)
{
    m_isTaken = taken;
}

void Bonus::accept(Visitor& v)
{
	v.visitBonus(this);
}

void Bonus::collisionEvent(Doodad& doodad)
{
	VisitorBonus v = VisitorBonus(this);
	doodad.accept(v);
}

void Bonus::update(float dt)
{
	m_body.update(dt);
    m_glowingTimer += dt;
    if(m_glowingTimer >= BONUS_GLOWING_DURATION)
        m_glowingTimer = 0.f;
}

void Bonus::render(sf::RenderWindow& window)
{
    if(isTaken())
        return;

	sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();

    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);
    shape.setRotation(m_body.getAngle());
	shape.setFillColor(BONUS_COLOR);

    float timeElaspedRatio = m_glowingTimer / BONUS_GLOWING_DURATION;
    float glowingSize = BONUS_SIZE + (BONUS_GLOWING_MAX_SIZE - BONUS_SIZE) * timeElaspedRatio;
    sf::RectangleShape glowingShape = getRectangleShapeForWindow(window, sf::Vector2f(glowingSize, glowingSize), position);
    glowingShape.setRotation(m_body.getAngle());

    sf::Color glowingColor = BONUS_GLOWING_COLOR;
    glowingColor.a = 200 * (1.f - timeElaspedRatio);
	glowingShape.setFillColor(glowingColor);

	window.draw(glowingShape);
	window.draw(shape);
}

