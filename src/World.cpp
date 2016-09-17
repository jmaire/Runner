#include <dirent.h>
#include "config.h"
#include "World.h"

std::vector<World> World::m_aWorld;

World::World(std::string name)
: m_name(name)
{}

World::World()
: World("")
{}

World::~World()
{}

std::string World::getName()
{
    return m_name;
}

void World::insereLevel(Level level)
{
    m_aLevel.push_back(level);
}

Level World::getLevel(unsigned int ind)
{
    return m_aLevel.at(ind);
}

std::vector<Level> World::getLevelList()
{
    return m_aLevel;
}

bool World::loadWorlds()
{
    DIR *dir = opendir(GAME_LEVELDIR);

	struct dirent *content;
	while((content = readdir(dir)) != nullptr)
	{
		std::string file = std::string(content->d_name);
        if(file.length() > 4 && ".xml" == (file.substr(file.length()-4, file.length()-1)))
        {
            loadWorldFile(GAME_LEVELDIR + file);
        }
	}

    closedir(dir);
    return true;
}

bool World::loadWorldFile(const std::string& worldFileLocation)
{
    tinyxml2::XMLDocument levelFile;
	levelFile.LoadFile(worldFileLocation.c_str());
	tinyxml2::XMLElement *elemRoot = levelFile.RootElement();

	std::string name = elemRoot->FirstChildElement("name")->GetText();
	World world = World(name);

    tinyxml2::XMLElement *elemLevel = elemRoot->FirstChildElement("level");
    while(nullptr != elemLevel)
    {
        Level level = Level(elemLevel);
        world.insereLevel(level);

        elemLevel = elemLevel->NextSiblingElement("level");
    }

    m_aWorld.push_back(world);
    return true;
}

void World::insereWorld(std::string name)
{
    m_aWorld.push_back(World(name));
}

World World::getWorld(unsigned int ind)
{
    return m_aWorld.at(ind);
}

Level World::getWorldLevel(unsigned int worldInd, unsigned int levelInd)
{
    World world = m_aWorld.at(worldInd);
    return world.getLevel(levelInd);
}


