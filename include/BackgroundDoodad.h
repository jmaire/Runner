#ifndef BACKGROUNDDOODAD_H
#define BACKGROUNDDOODAD_H

#include "Entity.h"

class BackgroundDoodad : public Entity
{
	public:
		virtual ~BackgroundDoodad(void);

		virtual void setDepth(int depth);
		//virtual void setBase(float base);

		virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

	protected:
	    int m_depth;

        BackgroundDoodad(void);
};

#endif // BACKGROUNDDOODAD_H
