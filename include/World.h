#ifndef WORLD_H
#define WORLD_H

#include "Level.h"

class World
{
    public:
        World(std::string name);
        World(void);

        virtual ~World(void);

        std::string getName(void);

        void insereLevel(Level level);
        Level getLevel(unsigned int ind);
        std::vector<Level> getLevelList();

        static bool loadWorlds(void);
        static bool loadWorldFile(const std::string& worldFileName);

        static World getWorld(unsigned int ind);
        static Level getWorldLevel(unsigned int worldInd, unsigned int levelInd);

    protected:
        std::string m_name;
        std::vector<Level> m_aLevel;

        static std::vector<World> m_aWorld;

        static void insereWorld(std::string name);

};

#endif // WORLD_H
