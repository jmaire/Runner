#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity
{
	public:
		Background(void);
		virtual ~Background(void);

		virtual void setDepth(int depth);
		virtual void setColor(sf::Color color);
		//virtual void setBase(float base);

		virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

	protected:
        int m_layoutDepth;
        sf::Color m_color;
};

#endif // BACKGROUND_H
