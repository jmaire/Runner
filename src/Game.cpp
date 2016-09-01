#include "Game.h"
#include "RessourcesManager.h"
#include "tinyxml2.h"

Level Game::m_level;

sf::View Game::m_camera;
bool Game::m_pause;

Character Game::m_character;
Exit Game::m_exit;
ListDoodad<Bonus> Game::m_bonusList;
ListDoodad<Rocket> Game::m_rocketList;
ListDoodad<Wall> Game::m_wallList;
std::vector<EstheticEffect*> Game::m_aEstheticEffect;

Game::Game()
{}

Game::~Game()
{}

void Game::setLevel(Level& level)
{
    m_level = level;
}

void Game::initLevel()
{
    m_character = m_level.getCharacter();
    m_exit = m_level.getExit();
    m_bonusList = m_level.getBonusList();
    m_wallList = m_level.getWallList();

    m_rocketList = ListDoodad<Rocket>();
}

void Game::collectEstheticEffect()
{
    EstheticEffect* ee = m_rocketList.popEstheticEffect();
    while(nullptr != ee)
    {
        m_aEstheticEffect.push_back(ee);
        ee = m_rocketList.popEstheticEffect();
    }
}

void Game::computeCamera(sf::RenderWindow& window)
{
	if(0 != m_character.getState())
		return;

	sf::Vector2f charactPos = m_character.getBody().getPosition();
	sf::Vector2f charactRec = m_character.getBody().getRectangle();

	int width = window.getSize().x;
	int height = window.getSize().y;

    float y_pos = charactPos.y + charactRec.y / 2.f;
    float yMin = m_level.getYMin();
    if(y_pos < yMin + height / 2.f)
		y_pos = yMin + height / 2.f;

	float x_max = m_exit.getBody().getXMax();
	float x_pos = charactPos.x + charactRec.x / 2.f + width / 4.f;
    if(x_pos > x_max - width / 2.f)
		x_pos = x_max - width / 2.f;

	m_camera.setSize(width, height);
	m_camera.setCenter(x_pos, height - y_pos);
}

void Game::collision()
{
	m_wallList.collision(m_character);
	m_rocketList.collision(m_character);
	m_bonusList.collision(m_character);
	m_exit.collision(m_character);

	std::vector<Rocket>& rocketList = m_rocketList.getList();
	for(unsigned int i=0; i<rocketList.size(); i++)
    {
        m_wallList.collision(rocketList.at(i));
    }
}

int Game::startLevel(sf::RenderWindow& window)
{
    initLevel();
	sf::Clock clock;

    m_pause = false;
	while(window.isOpen())
	{
		if(m_character.isDead())
			return 0;

		if(2 == m_character.getState())
			return 1;

		/// Compute all collisions
		collision();

		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			else if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                // Pause / unpause
                case sf::Keyboard::Escape:
                    m_pause = !m_pause;
                    break;

				// Restart level
                case sf::Keyboard::BackSpace:
                    return 0;
                    break;

				// Return to menu
                case sf::Keyboard::Delete:
                    return 1;
                    break;

                default:
	        		break;
	    		}
	  		}
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                switch(event.key.code)
                {
                case sf::Mouse::Left:
                    if(!m_pause)
                    {
                        m_rocketList.insereDoodad(m_character.launchRocket(window));
                    }
                    break;

                default:
                    break;
                }
            }
        }

        sf::Time elapsed = clock.restart();
		if(!m_pause)
		{
			update(elapsed.asSeconds());
		}

		window.clear(sf::Color(100,100,100));
		computeCamera(window);
		render(window);

		window.display();
	}

	return -1;
}

void Game::update(float dt)
{
    Body charBody = m_character.getBody();
    if(charBody.getYMax() < m_level.getYMin())
        m_character.setDead(true);

    float x_max = m_exit.getBody().getXMax();
    if(charBody.getXMin() > x_max)
        m_character.setDead(true);

    m_bonusList.update(dt);
    m_character.update(dt);
    m_exit.update(dt);
    m_rocketList.update(dt);
    m_wallList.update(dt);
    collectEstheticEffect();

    for(std::vector<EstheticEffect*>::iterator it=m_aEstheticEffect.begin(); it!=m_aEstheticEffect.end(); )
    {
        (*it)->update(dt);
        if((*it)->hasExpired())
        {
            EstheticEffect* tmp = *it;
            m_aEstheticEffect.erase(it);
            delete tmp;
        }
        else
            ++it;
    }
}

void Game::render(sf::RenderWindow& window)
{
    /// Drawing parallaxes
/*
    int iEnd = parallaxe.size();
    float percent_para = 1./(iEnd+1);

    sf::Sprite fond;
    sf::View v;
    v.setSize(window.getSize().x, window.getSize().y);

    for(int i=0; i < iEnd; i++)
    {
        fond.setTextureRect({-1000, -1000, 2000*(i+1), 2000*(i+1)});
        window.setView(v);
        v.setCenter(m_camera.getCenter().x*percent_para*(i+1),m_camera.getCenter().y*percent_para*(i+1));
        fond.setTexture(parallaxe[i]);
        fond.setPosition(-500,-500);
        window.draw(fond);
    }
*/
    /// render world

	window.setView(m_camera);
	m_character.render(window);
    m_exit.render(window);
    m_wallList.render(window);
    m_bonusList.render(window);

    for(std::vector<EstheticEffect*>::iterator it=m_aEstheticEffect.begin(); it!=m_aEstheticEffect.end(); ++it)
        (*it)->render(window);

    m_rocketList.render(window);

    /// drawing cursor

    if(!m_pause)
    {
        window.setMouseCursorVisible(false);
        sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window), m_camera);

        sf::Sprite cursor;
        cursor.setOrigin(16,16);
        cursor.setPosition(coord);
        cursor.setTexture(RessourcesManager::getCursor());
        window.draw(cursor);
	}
    else
    {
        window.setMouseCursorVisible(true);
        /// adding alpha when pause
        sf::RectangleShape shape;
        sf::Vector2u windowSize = window.getSize();
        shape.setSize(sf::Vector2f(windowSize.x, windowSize.y));
        sf::Vector2f posPause = window.getView().getCenter();
        posPause.x -= windowSize.x / 2.f;
        posPause.y -= windowSize.y / 2.f;
        shape.setPosition(posPause);
        shape.setFillColor(sf::Color(0, 0, 5, 200));
        window.draw(shape);
    }
}
