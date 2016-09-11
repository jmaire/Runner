#include "BackgroundBuilding.h"
#include "tools.h"

BackgroundBuilding::BackgroundBuilding()
: BackgroundDoodad()
{}

BackgroundBuilding::~BackgroundBuilding()
{}

void BackgroundBuilding::render(sf::RenderWindow& window)
{
    sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();
    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);

    sf::Color wallColor = BACKGROUND_BUILDING_WALL_COLOR;
    float colorFactor = 1.f / abs(m_depth);
    wallColor.r = wallColor.r * colorFactor;
    wallColor.g = wallColor.g * colorFactor;
    wallColor.b = wallColor.b * colorFactor;
	shape.setFillColor(wallColor);

	window.draw(shape);

    float windowFactor = 1.f / abs(m_depth);
	float windowSize = BACKGROUND_BUILDING_WINDOW_SIZE * windowFactor;
	float windowGap = BACKGROUND_BUILDING_WINDOW_GAP * windowFactor;
	sf::Vector2f windowRectangle = sf::Vector2f(windowSize, windowSize);

	unsigned int xWindowNumber = m_body.getRectangle().x / (windowSize + windowGap);
	unsigned int yWindowNumber = m_body.getRectangle().y / (windowSize + windowGap);

    sf::Vector2f pos = sf::Vector2f(m_body.getXMin() + (windowGap + windowSize) / 2.f, m_body.getYMin() + (windowGap + windowSize) / 2.f);
    for(unsigned int i=0; i<xWindowNumber; i++)
    {
        for(unsigned int j=0; j<yWindowNumber; j++)
        {
            sf::Vector2f windowPosition = sf::Vector2f(pos.x + i * (windowSize + windowGap), pos.y + j * (windowSize + windowGap));
            sf::RectangleShape windowShape = getRectangleShapeForWindow(window, windowRectangle, windowPosition);
            windowShape.setFillColor(BACKGROUND_BUILDING_WINDOW_COLOR);
            window.draw(windowShape);
        }
    }
}
