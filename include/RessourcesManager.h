#ifndef RESSOURCESMANAGER_H
#define RESSOURCESMANAGER_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class RessourcesManager
{
    public:
        virtual ~RessourcesManager();

        static void load(std::string dir);
        static void addPlan(const char* filepath);

        static std::vector<sf::Texture> plan;

        static sf::Texture& getCursor();
        static sf::Font& getFont();

    protected:
        static sf::Texture m_cursor;
        static sf::Font m_font;

    private:
        RessourcesManager();

};

#endif // RESSOURCESMANAGER_H
