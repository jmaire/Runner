#include "Menu.h"

#include <RessourcesManager.h>
#include "config.h"
#include "tinyxml2.h"

Menu::Menu()
{}

Menu::~Menu()
{}
/*
void Menu::computeCamera(sf::RenderWindow& window)
{
    //sf::Vector2u window_size = window.getSize();
    //this->camera.setCenter(window_size.x/2,window_size.y/2);
    //this->camera.setSize(window_size.x,window_size.y);
}

void Menu::loadingDirectories()
{
    DIR * rep = opendir(GAME_LEVELDIR);  /// opening directory "level"

    if (rep != nullptr)
    {
        struct dirent * content;
        int rep_number = 0;

        while((content = readdir(rep)) != nullptr)    /// parsing directory "level"
        {
            std::string subdir_name(content->d_name);
            if(subdir_name.find("world ") == 0)     /// looking for all sub-directory "world x"
            {
                rep_name.push_back(std::string(GAME_LEVELDIR + subdir_name));
                rep_number++;                       /// adding name of sub-directory to rep_name
            }
        }

        closedir(rep);

        for(unsigned int i=0;i<rep_name.size();i++)
        {
            rep = opendir(rep_name[i].data());      /// for each string in rep_name

            file_name.push_back(std::vector<std::string>());
            while((content = readdir(rep)) != nullptr)
            {
                if((int)std::string(content->d_name).find(".xml") != -1)
                {
                    file_name.back().push_back(content->d_name);    /// adding file which end by ".xml" to file_name[i]
                }                                               /// rep_name[i] = parent folder of file_name[i]
            }
        }
    }
}

void Menu::elementsPositionning(sf::RenderWindow& window)
{
    sf::Vector2u window_size = window.getSize();
    sprite_separation = sf::Vector2i(window_size.x/7,window_size.y/5); /// size optimal for 4 * 6 = 24 level per world

    int color_scale = 510/(rep_name.size()-1), c;       /// color difference between background

    for(unsigned int i=0 ; i<rep_name.size() ; i++)
    {
        spriteworld.push_back(sf::RectangleShape(sf::Vector2f(window_size.x,window_size.y)));   /// background of a world same size as window
        spriteworld.back().setPosition(window_size.x*i,0);      /// background of all world
        c = i*color_scale;

        if(c > 255)
            spriteworld[i].setFillColor(sf::Color(255,510-c,0,ALPHA_BACKGROUND));    /// color of background
        else
            spriteworld[i].setFillColor(sf::Color(c,255,0,ALPHA_BACKGROUND));

        spritelevel.push_back(std::vector<sf::CircleShape>());
        for(unsigned int j=0 ; j<file_name[i].size() ; j++)
        {
            spritelevel[i].push_back(sf::CircleShape(LEVEL_GRAPHICS_SIZE));
            spritelevel[i].back().setOrigin(LEVEL_GRAPHICS_SIZE,LEVEL_GRAPHICS_SIZE);  /// level representation
            spritelevel[i].back().setFillColor(sf::Color::Blue);
            spritelevel[i].back().setPosition(window_size.x*i+sprite_separation.x*(j%6+1),(j/6+1)*sprite_separation.y);
        }
    }

    this->computeCamera(window);

    sprite_char = sf::RectangleShape(sf::Vector2f(SELECTOR_SIZE,SELECTOR_SIZE));
    sprite_char.setFillColor(sf::Color::White);         /// selector
    sprite_char.setOrigin(SELECTOR_SIZE/2,SELECTOR_SIZE/2);
}


void Menu::initMenu()
{
    World::loadWorlds();
    m_worldInd = 0;


}

std::string Menu::startMenu(sf::RenderWindow& window)
{
    sf::Vector2u window_size = window.getSize();
    unsigned int cam_location=0, char_location=0;
    char levelnumber[20];

    sf::Text worldText;
    worldText.setFont(RessourcesManager::font);
    worldText.setColor(sf::Color::Black);
    worldText.setCharacterSize(30);

    sf::Text levelText;
    worldText.setFont(RessourcesManager::font);
    worldText.setColor(sf::Color::Black);
    worldText.setCharacterSize(20);

    while(window.isOpen())
	{
        sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		  	else if(event.type == sf::Event::MouseWheelMoved)    /// change world with wheel
            {
                cam_location += event.mouseWheel.delta;
                char_location = 0;
                if((int)cam_location < 0)
                    cam_location = 0;
                else if(cam_location >= file_name.size())
                    cam_location = file_name.size()-1;
            }
			if(event.type == sf::Event::MouseMoved)         /// move level selector
            {
                sf::Vector2f souris(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                unsigned int y__, next_char_location;
                if(souris.y < (y__ = window_size.y/2))
                {
                    if(souris.y < y__/2)
                        next_char_location = 0;
                    else
                        next_char_location = 6;
                }
                else
                {
                    if(souris.y < y__/2+y__)
                        next_char_location = 12;
                    else
                        next_char_location = 18;
                }
                unsigned int x__ = window_size.x/3;
                unsigned int x_scaling = window_size.x*cam_location;
                if(souris.x < x_scaling+x__)
                {
                    if(souris.x > x_scaling+x__/2)
                        next_char_location += 1;
                }
                else
                {
                    if(souris.x < x_scaling+x__*2)
                    {
                        if(souris.x < x_scaling+x__+x__/2)
                            next_char_location += 2;
                        else
                            next_char_location += 3;
                    }
                    else
                    {
                        if(souris.x < x_scaling+x__*2+x__/2)
                            next_char_location += 4;
                        else
                            next_char_location += 5;
                    }
                }
                if(next_char_location<spritelevel[cam_location].size())
                {
                    if(sqrt((spritelevel[cam_location][next_char_location].getPosition().x-souris.x)*(spritelevel[cam_location][next_char_location].getPosition().x-souris.x)+(spritelevel[cam_location][next_char_location].getPosition().y-souris.y)*(spritelevel[cam_location][next_char_location].getPosition().y-souris.y)) < 30)
                        char_location = next_char_location;
                }
            }
            if(event.type == sf::Event::MouseButtonPressed)     /// starts the level where the cursor is
            {
                return rep_name[cam_location]+'/'+file_name[cam_location][char_location];
            }
		  	if(event.type == sf::Event::KeyPressed)     /// change world with keyboard
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Up:      /// next world
                        {
                            if(cam_location<file_name.size()-1) cam_location++;
                            char_location = 0;
                        }
                        break;
                    case sf::Keyboard::Down:    /// previous world
                        {
                            if(cam_location>0) cam_location--;
                            char_location = 0;
                        }
                        break;
                    case sf::Keyboard::Return:  /// launch level
                        {
                            return rep_name[cam_location]+'/'+file_name[cam_location][char_location];
                        }
                        break;
                    default:;
                }
            }

		}

		this->camera.setCenter(cam_location*window_size.x+window_size.x/2,window_size.y/2); /// set camera on world selected

        sprite_char.setPosition(window_size.x*cam_location+sprite_separation.x*(char_location%6+1),(char_location/6+1)*sprite_separation.y); /// set cursor on level selected

        sprintf(levelnumber, "World %d Level %d",cam_location+1,char_location+1);   /// level name
        strname.setString(levelnumber);

        strname.setPosition(window_size.x*cam_location+(window_size.x-strname.getGlobalBounds().width)/2, 5);

        this->render(window);
	}
	return std::string("");
}

void Menu::update(float dt)
{}

void Menu::render(sf::RenderWindow& window)
{
        sf::Sprite cursor;
        cursor.setOrigin(16,16);
        cursor.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        cursor.setTexture(RessourcesManager::t_targ);

	    window.clear(sf::Color::Black);

	    sf::View camera;
        sf::Vector2u window_size = window.getSize();
        camera.setCenter(window_size.x/2,window_size.y/2);
        camera.setSize(window_size.x,window_size.y);
        window.setView(camera);

        for(unsigned int i=0 ; i<spriteworld.size() ; i++)
        {
            window.draw(this->spriteworld[i]);            /// background
            for(unsigned int j=0 ; j<spritelevel[i].size() ; j++)
            {
                window.draw(this->spritelevel[i][j]);     /// levels
            }
        }

        window.draw(this->sprite_char);                   /// selector
        window.draw(this->strname);                       /// title
        window.draw(cursor);                              /// cursor
		window.display();
}*/
