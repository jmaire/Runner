#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"
#include "Exit.h"
#include "ListDoodad.h"
#include "RocketLauncher.h"
#include "Wall.h"
#include "tinyxml2.h"

class Level
{
    public:
        Level(void);
        Level(tinyxml2::XMLElement *elem);

        virtual ~Level(void);

        std::string getName(void);
        float getYMin(void);

        Character getCharacter(void);
        Exit getExit(void);
        ListDoodad<Bonus> getBonusList(void);
        ListDoodad<RocketLauncher> getRocketLauncherList(void);
        ListDoodad<Wall> getWallList(void);

    protected:
        std::string m_name;
        float m_yMin;

        Character m_character;
        Exit m_exit;
        ListDoodad<Bonus> m_bonusList;
        ListDoodad<RocketLauncher> m_rocketLauncherList;
        ListDoodad<Wall> m_wallList;

};

#endif // LEVEL_H
