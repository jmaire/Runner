#ifndef BACKGROUNDDOODAD_H
#define BACKGROUNDDOODAD_H

#include "Entity.h"

class BackgroundDoodad : public Entity
{
	public:
		BackgroundDoodad(void);
		virtual ~BackgroundDoodad(void);

		virtual void setColor(sf::Color color);
		//virtual void setBase(float base);

		virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

	protected:
        sf::Color m_color;
};

#endif // BACKGROUNDDOODAD_H
