#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"
#include "Exit.h"
#include "ListDoodad.h"
#include "Wall.h"
#include "tinyxml2.h"

class Level
{
    public:
        Level();
        Level(tinyxml2::XMLElement *elem);

        virtual ~Level();

        float getYMin();

        Character getCharacter();
        Exit getExit();
        ListDoodad<Bonus> getBonusList();
        ListDoodad<Wall> getWallList();

    protected:
        std::string m_name;
        float m_yMin;

        Character m_character;
        Exit m_exit;
        ListDoodad<Bonus> m_bonusList;
        ListDoodad<Wall> m_wallList;

};

#endif // LEVEL_H
