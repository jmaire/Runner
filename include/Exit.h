#ifndef EXIT_H
#define EXIT_H

#include "Doodad.h"
//#include "VisitorExit.h"

const float EXIT_SIZE = 15.f;
const sf::Vector2f EXIT_RECTANGLE = sf::Vector2f(EXIT_SIZE, EXIT_SIZE*9);
const sf::Color EXIT_COLOR = sf::Color(255, 255, 255, 255);

class Exit : public Doodad
{
    public:
        Exit(void);
        Exit(sf::Vector2f pos);

        virtual ~Exit(void);

        virtual bool isReached(void);
        virtual void setReached(bool reached);

        virtual void accept(Visitor& v);

        virtual void render(sf::RenderWindow& window);

    protected:
        bool m_reached;
};

#endif // EXIT_H
