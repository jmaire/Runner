#ifndef BACKGROUNDBUILDING_H
#define BACKGROUNDBUILDING_H

#include "BackgroundDoodad.h"

const float BACKGROUND_BUILDING_WINDOW_SIZE = 60.f;
const float BACKGROUND_BUILDING_WINDOW_GAP = 100.f;
const sf::Color BACKGROUND_BUILDING_WALL_COLOR = sf::Color(50, 50, 50);
const sf::Color BACKGROUND_BUILDING_WINDOW_COLOR = sf::Color(150, 150, 50);

class BackgroundBuilding : public BackgroundDoodad
{
    public:
        BackgroundBuilding(void);
        virtual ~BackgroundBuilding(void);

        virtual void render(sf::RenderWindow& window);
};

#endif // BACKGROUNDBUILDING_H
