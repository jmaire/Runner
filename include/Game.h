#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "EstheticEffect.h"
#include "Rocket.h"

const float LEVEL_CAMERA_BORDER_OFFSET = 60.f;

class Game
{
    public:
        virtual ~Game(void);

        static void setLevel(Level& level);
        static void initLevel(void);

        static void collectEstheticEffect(void);
        static void computeCamera(sf::RenderWindow& window);

        static void collision(void);

        static int startLevel(sf::RenderWindow& window);

        static void update(float dt);
        static void render(sf::RenderWindow& window);
        static void renderUI(sf::RenderWindow& window);

        //std::vector<sf::Texture> parallaxe;

    protected:
        static Level m_level;

        static sf::View m_camera;
        static sf::View m_cameraUI;

        static bool m_pause;
        static Character m_character;
        static Exit m_exit;
        static ListDoodad<Bonus> m_bonusList;
        static ListDoodad<Rocket> m_rocketList;
        static ListDoodad<Wall> m_wallList;

        static std::vector<EstheticEffect*> m_aEstheticEffect;

        static float m_uiBonusAngle;
        static float m_uiBonusGlowingTimer;

    private:
        Game(void);

};

#endif // GAME_H
