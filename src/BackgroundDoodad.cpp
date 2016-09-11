#include <SFML/Graphics/RectangleShape.hpp>
#include "BackgroundDoodad.h"
#include "tools.h"

BackgroundDoodad::BackgroundDoodad()
: Entity()
, m_depth(0)
{}

BackgroundDoodad::~BackgroundDoodad()
{}

void BackgroundDoodad::setDepth(int depth)
{
    m_depth = depth;
}

void BackgroundDoodad::update(float dt)
{
	m_body.update(dt);
}

void BackgroundDoodad::render(sf::RenderWindow& window)
{}
