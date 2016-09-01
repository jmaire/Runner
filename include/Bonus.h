#ifndef BONUS_H
#define BONUS_H

#include "VisitorBonus.h"

const float BONUS_SIZE = 15.f;
const sf::Vector2f BONUS_RECTANGLE = sf::Vector2f(BONUS_SIZE, BONUS_SIZE);
const sf::Color BONUS_COLOR = sf::Color(255, 0, 255, 255);

class Bonus : public Doodad
{
public:
	Bonus();
	Bonus(sf::Vector2f pos);

	~Bonus();

	virtual void accept(Visitor& v);
	virtual void collisionEvent(Doodad* doodad);

	void render(sf::RenderWindow& window);
};

#endif // BONUS_H
