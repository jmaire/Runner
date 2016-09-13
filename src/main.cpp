#include "config.h"
#include "Game.h"
//#include "Menu.h"
#include "RessourcesManager.h"
#include "World.h"

#include "Character.h"

//using namespace runner;

int main(int argc, char *argv[])
{
    World::loadWorlds();

	// initialize
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Runner", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(120);
    window.clear(sf::Color(0,0,0,255));

    RessourcesManager::load(GAME_IMAGEDIR);

	int reset = 1;
	do
	{
		do
		{
		    Level level = World::getWorldLevel(0,0);
		    Game::setLevel(level);
			reset = Game::startLevel(window);
		}
		while(0 == reset);
	}
	while(1 == reset);

	return 0;
}
