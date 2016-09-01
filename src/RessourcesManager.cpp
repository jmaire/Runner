#include <RessourcesManager.h>

sf::Texture RessourcesManager::m_cursor;
sf::Font RessourcesManager::m_font;
std::vector<sf::Texture> RessourcesManager::plan;

RessourcesManager::~RessourcesManager()
{}

void RessourcesManager::load(std::string dir)
{
    m_cursor.loadFromFile(dir + "viseur.png");
    m_font.loadFromFile(dir + "consolab.ttf");
}

void RessourcesManager::addPlan(const char* filepath)
{
    sf::Texture t;
    t.loadFromFile(filepath);
    t.setRepeated(true);
    plan.push_back(t);
}

sf::Texture& RessourcesManager::getCursor()
{
    return m_cursor;
}

sf::Font& RessourcesManager::getFont()
{
    return m_font;
}
