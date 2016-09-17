#include "RocketLauncher.h"
#include "tools.h"

RocketLauncher::RocketLauncher()
: Doodad()
, m_target(nullptr)
, m_fireCooldown(ROCKET_LAUNCHER_FIRE_COOLDOWN)
{
    m_body.setRectangle(ROCKET_LAUNCHER_RECTANGLE);
}

RocketLauncher::RocketLauncher(sf::Vector2f pos)
: RocketLauncher()
{
    m_body.setPosition(pos);
}

RocketLauncher::~RocketLauncher()
{
    for(std::vector<Rocket*>::iterator it=m_rocketList.begin(); it!=m_rocketList.end(); )
    {
        Rocket* tmp = *it;
        m_rocketList.erase(it);
        delete tmp;
    }
}

void RocketLauncher::setTarget(Doodad* target)
{
    m_target = target;
}

void RocketLauncher::launchRocket()
{
    if(nullptr == m_target)
        return;

    Rocket *rocket = new Rocket(m_body.getPosition(), m_body.getVelocity());
    rocket->setTarget(m_target);
    m_rocketList.push_back(rocket);
}

Rocket* RocketLauncher::popRocket()
{
    if(m_rocketList.empty())
        return nullptr;

    Rocket* rocket = m_rocketList.at(0);
    m_rocketList.erase(m_rocketList.begin());
    return rocket;
}

void RocketLauncher::update(float dt)
{
    m_body.update(dt);

    m_fireCooldown -= dt;
    if(m_fireCooldown <= 0.f)
    {
        launchRocket();
        m_fireCooldown = ROCKET_LAUNCHER_FIRE_COOLDOWN;
    }
}

void RocketLauncher::render(sf::RenderWindow& window)
{
    sf::Vector2f rectangle = m_body.getRectangle();
    sf::Vector2f position = m_body.getPosition();
    sf::RectangleShape shape = getRectangleShapeForWindow(window, rectangle, position);
	shape.setFillColor(ROCKET_LAUNCHER_COLOR);
	shape.setRotation(45.f);
	window.draw(shape);

	if(nullptr == m_target)
        return;

	sf::Vector2f launcherPosition = m_body.getPosition();
    sf::Vector2f targetPosition = m_target->getBody().getPosition();
    sf::Vector2f trajectory = sf::Vector2f(targetPosition.y - launcherPosition.y, targetPosition.x - launcherPosition.x);
    float angle = atan2(trajectory.x, trajectory.y);
    sf::Vector2f weaponPosition = sf::Vector2f(position.x + cos(angle) * ROCKET_LAUNCHER_WEAPON_LENGHT / 3.f, position.y + sin(angle) * ROCKET_LAUNCHER_WEAPON_LENGHT / 3.f);
    sf::RectangleShape weaponShape = getRectangleShapeForWindow(window, ROCKET_LAUNCHER_WEAPON_RECTANGLE, weaponPosition);
	weaponShape.setFillColor(ROCKET_LAUNCHER_WEAPON_COLOR);
	weaponShape.setRotation(-angle * 180.f / M_PI);
	window.draw(weaponShape);
}
