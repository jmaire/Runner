#include "BackgroundBuilding.h"//
#include "BackgroundMoon.h"//
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
ListDoodad<RocketLauncher> Game::m_rocketLauncherList;
ListDoodad<Wall> Game::m_wallList;

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
    m_rocketLauncherList = m_level.getRocketLauncherList();
    m_wallList = m_level.getWallList();

    std::vector<RocketLauncher>& rocketLauncherList = m_rocketLauncherList.getList();
    for(std::vector<RocketLauncher>::iterator it=rocketLauncherList.begin(); it!=rocketLauncherList.end(); ++it)
    {
        it->setTarget(&m_character);
    }

    m_rocketList = ListDoodad<Rocket>();

    EstheticEffectManager::clear();

    BackgroundManager::clear();
    BackgroundManager::reset();

    BackgroundBuilding *bg = new BackgroundBuilding();//
    bg->setRectangle(sf::Vector2f(400.f,500.f));
    bg->setPosition(sf::Vector2f(0.f, 250.f));
    BackgroundManager::insertBackgroundDoodad(-1, bg);

	bg = new BackgroundBuilding();//
    bg->setRectangle(sf::Vector2f(400.f,800.f));
    bg->setPosition(sf::Vector2f(0.f, 250.f));
    BackgroundManager::insertBackgroundDoodad(-4, bg);

	bg = new BackgroundBuilding();//
    bg->setRectangle(sf::Vector2f(200.f,600.f));
    bg->setPosition(sf::Vector2f(500.f, 250.f));
    BackgroundManager::insertBackgroundDoodad(-2, bg);

    BackgroundMoon *bg2 = new BackgroundMoon();
    bg2->setRectangle(sf::Vector2f(40.f,500.f));
    bg2->setPosition(sf::Vector2f(200.f, 800.f));
    BackgroundManager::insertBackgroundDoodad(-5,bg2);
}

void Game::setPause(bool pause, sf::RenderWindow& window)
{
    m_pause = pause;
    window.setMouseCursorVisible(m_pause);
}

void Game::collectEstheticEffect()
{
    EstheticEffect* ee;
    ee = m_rocketList.popEstheticEffect();
    while(nullptr != ee)
    {
        EstheticEffectManager::insertEstheticEffect(ee);
        ee = m_rocketList.popEstheticEffect();
    }

    ee = m_wallList.popEstheticEffect();
    while(nullptr != ee)
    {
        EstheticEffectManager::insertEstheticEffect(ee);
        ee = m_wallList.popEstheticEffect();
    }

    ee = m_bonusList.popEstheticEffect();
    while(nullptr != ee)
    {
        EstheticEffectManager::insertEstheticEffect(ee);
        ee = m_bonusList.popEstheticEffect();
    }
}

void Game::collectRocket()
{
    std::vector<RocketLauncher>& rocketLauncherList = m_rocketLauncherList.getList();
    for(std::vector<RocketLauncher>::iterator it=rocketLauncherList.begin(); it!=rocketLauncherList.end(); ++it)
    {
        Rocket* rocket = it->popRocket();
        while(nullptr != rocket)
        {
            m_rocketList.insereDoodad(*rocket);
            rocket = it->popRocket();
        }
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

    //m_cameraUI.setViewport(sf::FloatRect(0.f, 0.f, width/(width+height), height/(width+height)));
    m_cameraUI.setCenter(width / 2.f, height / 2.f);
    m_cameraUI.setSize(width, height);
}

void Game::collision()
{
	m_rocketList.collision(m_character);
	m_character.collision(m_exit);

    std::vector<Bonus>& bonusList = m_bonusList.getList();
    for(std::vector<Bonus>::iterator it=bonusList.begin(); it!=bonusList.end(); ++it)
        m_character.collision(*it);

    std::vector<Wall>& wallList = m_wallList.getList();
    for(std::vector<Wall>::iterator it=wallList.begin(); it!=wallList.end(); ++it)
    {
        m_character.collision(*it);
        m_rocketList.collision(*it);
    }

    std::vector<Rocket>& rocketList = m_rocketList.getList();
    for(std::vector<Rocket>::iterator it=rocketList.begin(); it!=rocketList.end(); ++it)
    {
        m_rocketList.collision(*it);
    }
}

int Game::startLevel(sf::RenderWindow& window)
{
    initLevel();
	sf::Clock clock;

    m_pause = false;
	while(window.isOpen())
	{
		if(!window.hasFocus())
			setPause(true, window);

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
			else if(event.type == sf::Event::Resized || event.type == sf::Event::LostFocus)
                setPause(true, window);
			else if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
					// Pause / unpause
					case sf::Keyboard::Escape:
						setPause(!m_pause, window);
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
		window.setView(m_camera);
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

    m_rocketLauncherList.update(dt);
    collectRocket();

    m_rocketList.update(dt);
    m_wallList.update(dt);
    collectEstheticEffect();

    BackgroundManager::update(dt);
    EstheticEffectManager::update(dt);

    m_uiBonusAngle += BONUS_ANGULAR_VELOCITY / 2.f * dt;
    m_uiBonusGlowingTimer += dt;
    if(m_uiBonusGlowingTimer >= BONUS_GLOWING_DURATION)
        m_uiBonusGlowingTimer = 0.f;
}

void Game::render(sf::RenderWindow& window)
{
	window.setView(m_camera);
    BackgroundManager::render(window);
    m_exit.render(window);
    m_wallList.render(window);
    m_bonusList.render(window);
    m_rocketLauncherList.render(window);
    m_rocketList.render(window);
	m_character.render(window);

	EstheticEffectManager::render(window);

    /// drawing cursor
    if(m_pause)
    {
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
    else
    {
        sf::Vector2f coord = window.mapPixelToCoords(sf::Mouse::getPosition(window), m_camera);
        sf::Sprite cursor;
        cursor.setOrigin(16,16);
        cursor.setPosition(coord);
        cursor.setTexture(RessourcesManager::getCursor());
        window.draw(cursor);
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

    char buff[64];
    sprintf(buff,"x%d",bonusCount);
    sf::Text bonusText = sf::Text(buff, RessourcesManager::getFont(), 48);
    bonusText.setPosition(sf::Vector2f(60.f, 0.f));

    //sprintf(buff,"%s - %s",bonusCount);
    sf::Text levelText = sf::Text(m_level.getName(), RessourcesManager::getFont(), 48);
    levelText.setPosition(sf::Vector2f(1000.f, 0.f));

    window.setView(m_cameraUI);
    window.draw(barShape);
    window.draw(bonusText);
    window.draw(levelText);
    window.draw(bonusGlowingShape);
    window.draw(bonusShape);

	if(m_pause)
	{
		sf::Text pauseText = sf::Text("Pause", RessourcesManager::getFont(), 64);
		pauseText.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
		window.draw(pauseText);
	}
}
