#ifndef CHARACTER_H
#define CHARACTER_H

#include <cmath>

#include "VisitorCharacter.h"

const float CHARACTER_MASS = 5.f;
const float CHARACTER_SIZE = 30.f;
const sf::Vector2f CHARACTER_RECTANGLE = sf::Vector2f(CHARACTER_SIZE, CHARACTER_SIZE);
const float VELOCITY_X = 250.f;
const sf::Color CHARACTER_COLOR = sf::Color(60, 120, 150, 255);
const float CHARACTER_WEAPON_LENGHT = 25.f;
const sf::Vector2f CHARACTER_WEAPON_RECTANGLE = sf::Vector2f(CHARACTER_WEAPON_LENGHT, 15.f);
const sf::Color CHARACTER_WEAPON_COLOR = sf::Color(80, 150, 200, 255);

class Character : public Doodad
{
public:
	Character(void);
	Character(sf::Vector2f pos);

	virtual ~Character(void);

    void setRun(bool isRunning);

	void setDead(bool isDead);
	bool isDead(void);

	Rocket launchRocket(sf::RenderWindow& window);

	virtual void accept(Visitor& v);
	virtual void collisionEvent(Doodad& doodad);

	virtual void update(float dt);
	virtual void render(sf::RenderWindow& window);

private:
	bool m_isRunning, m_isDead;

};

#endif // CHARACTER_H
