#ifndef RESSOURCESMANAGER_H
#define RESSOURCESMANAGER_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class RessourcesManager
{
    public:
        virtual ~RessourcesManager(void);

        static void load(std::string dir);
        static void addPlan(const char* filepath);

        static std::vector<sf::Texture> plan;

        static sf::Texture& getCursor(void);
        static sf::Font& getFont(void);

    protected:
        static sf::Texture m_cursor;
        static sf::Font m_font;

    private:
        RessourcesManager(void);

};

#endif // RESSOURCESMANAGER_H
