#include <SFML/Window/Mouse.hpp>
#include "Character.h"
#include "tools.h"

Character::Character()
: Doodad()
, m_isRunning(false)
, m_isDead(false)
{
    m_body.setRectangle(CHARACTER_RECTANGLE);
    m_body.setMass(CHARACTER_MASS);
    m_body.setGravity(true);
}

Character::Character(sf::Vector2f pos)
: Character()
{
	m_body.setPosition(pos);
}

Character::~Character()
{}

void Character::setRun(bool isRunning)
{
	m_isRunning = isRunning;
}

void Character::setDead(bool isDead)
{
    m_isDead = isDead;
}

bool Character::isDead()
{
    return m_isDead;
}
#include <stdio.h>//
Rocket Character::launchRocket(sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    mousePos.y = window.getSize().y - mousePos.y;

    sf::Vector2f pos = m_body.getPosition();// + m_body.getRectangle() / 2.f;

    sf::Vector2f trajectory = sf::Vector2f(mousePos.y-pos.y,mousePos.x-pos.x);
    float angle = atan2(trajectory.x, trajectory.y);
    sf::Vector2f vel = sf::Vector2f(cos(angle)*ROCKET_VELOCITY,sin(angle)*ROCKET_VELOCITY);

	return Rocket(pos, vel + m_body.getVelocity());
}

void Character::accept(Visitor& v)
{
	v.visitCharacter(this);
}

void Character::collisionEvent(Doodad& doodad)
{
	VisitorCharacter v = VisitorCharacter(this);
	doodad.accept(v);
}

void Character::update(float dt)
{
	sf::Vector2f vel = m_body.getVelocity();

	if(m_isRunning)
	{
		m_isRunning = false;
		vel.x = VELOCITY_X;
	}

	m_body.setVelocity(vel);
	m_body.update(dt);
}

void Character::render(sf::RenderWindow& window)
{
	sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();
    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);

	shape.setFillColor(CHARACTER_COLOR);

	window.draw(shape);
}
