#ifndef CHARACTER_H
#define CHARACTER_H

#include <cmath>

#include "VisitorCharacter.h"

const float CHARACTER_MASS = 5.f;
const float CHARACTER_SIZE = 30.f;
const sf::Vector2f CHARACTER_RECTANGLE = sf::Vector2f(CHARACTER_SIZE, CHARACTER_SIZE);
const float VELOCITY_X = 250.f;
const sf::Color CHARACTER_COLOR = sf::Color(0, 0, 255, 255);
//const int CHARACTER_GRAY = 0.299*CHARACTER_COLOR.r + 0.587*CHARACTER_COLOR.g + 0.587*CHARACTER_COLOR.b;
//const sf::Color CHARACTER_GRAY_COLOR = sf::Color(CHARACTER_GRAY, CHARACTER_GRAY, CHARACTER_GRAY, CHARACTER_COLOR.a);

class Character : public Doodad
{
public:
	Character();
	Character(sf::Vector2f pos);

	virtual ~Character();

    void setRun(bool isRunning);

	void setDead(bool isDead);
	bool isDead();

	Rocket launchRocket(sf::RenderWindow& window);

	virtual void accept(Visitor& v);
	virtual void collisionEvent(Doodad& doodad);

	virtual void update(float dt);
	virtual void render(sf::RenderWindow& window);

private:
	bool m_isRunning, m_isDead;

};

#endif // CHARACTER_H
