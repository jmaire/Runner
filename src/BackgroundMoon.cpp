#include "BackgroundMoon.h"
#include "tools.h"

BackgroundMoon::BackgroundMoon()
: BackgroundDoodad()
, m_glowingTimer(0.f)
{}

BackgroundMoon::~BackgroundMoon()
{}

void BackgroundMoon::update(float dt)
{
    m_glowingTimer += dt;
    if(m_glowingTimer >= BACKGROUND_MOON_GLOWING_DURATION)
        m_glowingTimer = 0.f;
}

void BackgroundMoon::render(sf::RenderWindow& window)
{
    sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();
    sf::CircleShape shape = getCircleShapeForWindow(window, rectangle.x, position);
    //shape.setPointCount(32);
    shape.setFillColor(BACKGROUND_MOON_COLOR);

    float timeElaspedRatio = m_glowingTimer / BACKGROUND_MOON_GLOWING_DURATION;
    float glowingSize = rectangle.x + BACKGROUND_MOON_GLOWING_BONUS_SIZE * timeElaspedRatio;
    sf::CircleShape glowingShape = getCircleShapeForWindow(window, glowingSize, position);

    sf::Color glowingColor = BACKGROUND_MOON_COLOR;
    glowingColor.a = 200 * (1.f - timeElaspedRatio);
	glowingShape.setFillColor(glowingColor);

	window.draw(glowingShape);
	window.draw(shape);
}
