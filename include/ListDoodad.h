#ifndef LISTDOODAD_H
#define LISTDOODAD_H

#include <vector>
#include "Doodad.h"

template <typename T=Doodad>
class ListDoodad
{
    public:
        ListDoodad(void);
        virtual ~ListDoodad(void);

        virtual unsigned int size(void);
        virtual T& getDoodad(int i);
        virtual std::vector<T>& getList(void);

        virtual void insereDoodad(T doodad);

        virtual void collision(Doodad& doodad);
        //virtual void collisionList(ListDoodad<Doodad>& doodad);

        virtual EstheticEffect* popEstheticEffect(void);

        virtual void update(float dt);
        virtual void render(sf::RenderWindow& window);

    protected:
        std::vector<T> m_doodads;
};

#include "../src/ListDoodad.tpp"

#endif // LISTDOODAD_H
