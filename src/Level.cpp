#include "Level.h"
#include "tools.h"

Level::Level()
{}

Level::Level(tinyxml2::XMLElement *elem)
: Level()
{
    // Name
	tinyxml2::XMLElement *elemName = elem->FirstChildElement("name");
    m_name = elemName->GetText();

    // Character
	tinyxml2::XMLElement *elemCharacter = elem->FirstChildElement("character");
	tinyxml2::XMLElement *elemPosition = elemCharacter->FirstChildElement("position");
	sf::Vector2f characterPosition = sf::Vector2f(elemPosition->DoubleAttribute("posX"),elemPosition->DoubleAttribute("posY"));
    m_character = Character(characterPosition);
    m_yMin = m_character.getBody().getYMin();

	// Exit
	tinyxml2::XMLElement *elemExit = elem->FirstChildElement("exit");
	elemPosition = elemExit->FirstChildElement("position");
    sf::Vector2f exitPosition = sf::Vector2f(elemPosition->DoubleAttribute("posX"),elemPosition->DoubleAttribute("posY"));
    m_exit = Exit(exitPosition);
    m_yMin = MY_MIN(m_yMin, m_exit.getBody().getYMin());

	// Obstacle
    tinyxml2::XMLElement *elemWall = elem->FirstChildElement("wall");
    while(nullptr != elemWall)
    {
        bool isDestructible = "true" == (std::string)(elemWall->Attribute("destructible"));

        elemPosition = elemWall->FirstChildElement("position");
        sf::Vector2f wallPosition = sf::Vector2f(elemPosition->DoubleAttribute("posX"),elemPosition->DoubleAttribute("posY"));

        tinyxml2::XMLElement *elemDimension = elemWall->FirstChildElement("dimension");
        sf::Vector2f wallDimension = sf::Vector2f(elemDimension->DoubleAttribute("width"),elemDimension->DoubleAttribute("height"));

        Wall wall = Wall(wallDimension, wallPosition);
        wall.setDestructible(isDestructible);
        m_wallList.insereDoodad(wall);
        m_yMin = MY_MIN(m_yMin, wall.getBody().getYMin());

        elemWall = elemWall->NextSiblingElement("wall");
    }

    //m_yMin -= LEVEL_CAMERA_BORDER_OFFSET;

    // Bonus
    tinyxml2::XMLElement *elemBonus = elem->FirstChildElement("bonus");
    while(nullptr != elemBonus)
    {
        elemPosition = elemBonus->FirstChildElement("position");
        sf::Vector2f bonusPosition = sf::Vector2f(elemPosition->DoubleAttribute("posX"),elemPosition->DoubleAttribute("posY"));
        Bonus bonus = Bonus(bonusPosition);
        m_bonusList.insereDoodad(bonus);

        m_yMin = MY_MIN(m_yMin, bonus.getBody().getYMin());

        elemBonus = elemBonus->NextSiblingElement("bonus");
    }
}

Level::~Level()
{}

float Level::getYMin()
{
    return m_yMin;
}

Character Level::getCharacter()
{
    return m_character;
}

Exit Level::getExit()
{
    return m_exit;
}

ListDoodad<Bonus> Level::getBonusList()
{
    return m_bonusList;
}

ListDoodad<Wall> Level::getWallList()
{
    return m_wallList;
}
