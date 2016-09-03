#include "Game.h"
#include "RessourcesManager.h"
#include "tinyxml2.h"
#include "tools.h"

Level Game::m_level;

sf::View Game::m_camera;
sf::View Game::m_cameraUI;
bool Game::m_pause;

Character Game::m_character;
Exit Game::m_exit;
ListDoodad<Bonus> Game::m_bonusList;
ListDoodad<Rocket> Game::m_rocketList;
ListDoodad<Wall> Game::m_wallList;
std::vector<EstheticEffect*> Game::m_aEstheticEffect;

float Game::m_uiBonusAngle;
float Game::m_uiBonusGlowingTimer;

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
    m_aEstheticEffect.clear();
}

void Game::collectEstheticEffect()
{
    EstheticEffect* ee;
    ee = m_rocketList.popEstheticEffect();
    while(nullptr != ee)
    {
        m_aEstheticEffect.push_back(ee);
        ee = m_rocketList.popEstheticEffect();
    }

    ee = m_wallList.popEstheticEffect();
    while(nullptr != ee)
    {
        m_aEstheticEffect.push_back(ee);
        ee = m_wallList.popEstheticEffect();
    }

    ee = m_bonusList.popEstheticEffect();
    while(nullptr != ee)
    {
        m_aEstheticEffect.push_back(ee);
        ee = m_bonusList.popEstheticEffect();
    }
}

void Game::computeCamera(sf::RenderWindow& window)
{
	sf::Vector2f charactPos = m_character.getBody().getPosition();

	int width = window.getSize().x;
	int height = window.getSize().y;

	sf::Vector2f cameraCenter;
    cameraCenter.x = MY_MIN(m_exit.getBody().getXMax() - width / 2.f, charactPos.x + width / 4.f);
    cameraCenter.y = height - MY_MAX(m_level.getYMin() + height / 2.f, charactPos.y);

	m_camera.setSize(width, height);
	m_camera.setCenter(cameraCenter);

    m_cameraUI.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void Game::collision()
{
	m_wallList.collision(m_character);
	m_rocketList.collision(m_character);
	m_bonusList.collision(m_character);
	m_exit.collision(m_character);

	//m_rocketList.collisionList(m_wallList);

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
/*
		if(2 == m_character.getState())
			return 1;
*/
		// Compute all collisions
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

		window.clear(GAME_BACKGROUND_COLOR);
		computeCamera(window);
		render(window);
		renderUI(window);

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

    collectEstheticEffect();
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

    m_uiBonusAngle += BONUS_ANGULAR_VELOCITY * dt;
    m_uiBonusGlowingTimer += dt;
    if(m_uiBonusGlowingTimer >= BONUS_GLOWING_DURATION)
        m_uiBonusGlowingTimer = 0.f;
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
    m_exit.render(window);
    m_wallList.render(window);
    m_bonusList.render(window);
	m_character.render(window);

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

void Game::renderUI(sf::RenderWindow& window)
{
    sf::RectangleShape barShape;// TODO
    barShape.setSize(sf::Vector2f(window.getSize().x, 70.f));
    barShape.setPosition(sf::Vector2f(0.f,0.f));
    //barShape.setOrigin(barShape.getSize() / 2.f);
    barShape.setFillColor(sf::Color(0,0,0,100));

    sf::Vector2f rectangle = sf::Vector2f(30.f, 30.f);
    sf::Vector2f position = sf::Vector2f(30.f, 35.f);

    sf::RectangleShape bonusShape;
    bonusShape.setSize(rectangle);
    bonusShape.setPosition(position);
    bonusShape.setOrigin(bonusShape.getSize() / 2.f);
    bonusShape.setFillColor(BONUS_COLOR);
    bonusShape.setRotation(m_uiBonusAngle);

    float timeElaspedRatio = m_uiBonusGlowingTimer / BONUS_GLOWING_DURATION;
    float glowingSize = 30.f + 20.f * timeElaspedRatio;
    sf::RectangleShape bonusGlowingShape;
    bonusGlowingShape.setSize(sf::Vector2f(glowingSize, glowingSize));
    bonusGlowingShape.setPosition(position);
    bonusGlowingShape.setOrigin(bonusGlowingShape.getSize() / 2.f);
    bonusGlowingShape.setRotation(m_uiBonusAngle);

    sf::Color glowingColor = BONUS_GLOWING_COLOR;
    glowingColor.a = 200 * (1.f - timeElaspedRatio);
	bonusGlowingShape.setFillColor(glowingColor);

	unsigned int bonusCount = 0;
	std::vector<Bonus> bonusList = m_bonusList.getList();
	for(std::vector<Bonus>::iterator it = bonusList.begin(); it != bonusList.end(); ++it)
    {
        if(it->isTaken())
            bonusCount++;
    }

    char buff[8];
    sprintf(buff,"x%d",bonusCount);
    sf::Text bonusText = sf::Text(buff, RessourcesManager::getFont(), 48);
    bonusText.setPosition(sf::Vector2f(60.f, 0.f));

    window.setView(m_cameraUI);
    window.draw(barShape);
    window.draw(bonusText);
    window.draw(bonusGlowingShape);
    window.draw(bonusShape);


    window.setView(m_camera);
}
