#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include <map>
#include "BackgroundDoodad.h"

class BackgroundManager
{
    public:
        virtual ~BackgroundManager(void);

        static void clear(void);
        static void reset(void);

        static void insertBackgroundDoodad(int depth, BackgroundDoodad* background);

        static void update(float dt);
        static void render(sf::RenderWindow& window);

    protected:
        static int m_minDepth, m_maxDepth;
        static std::map<int,std::vector<BackgroundDoodad*>> m_aBackground;

    private:
        BackgroundManager(void);

};

#endif // BACKGROUNDMANAGER_H
