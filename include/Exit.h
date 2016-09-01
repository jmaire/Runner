#ifndef EXIT_H
#define EXIT_H

#include "VisitorExit.h"

const float EXIT_SIZE = 15.f;
const sf::Vector2f EXIT_RECTANGLE = sf::Vector2f(EXIT_SIZE, EXIT_SIZE*9);
const sf::Color EXIT_COLOR = sf::Color(255, 255, 255, 255);

class Exit : public Doodad
{
public:
    Exit();
    Exit(sf::Vector2f pos);

    virtual ~Exit();

	virtual void accept(Visitor& v);
	void collisionEvent(Doodad* doodad);

    //virtual void update(float dt);
	virtual void render(sf::RenderWindow& window);

private:
    //sf::Vector2<const float> positionAncrage;
};

#endif // EXIT_H