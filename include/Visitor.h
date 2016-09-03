#ifndef VISITOR_H
#define VISITOR_H

#include "Doodad.h"

class Bonus;
class Character;
class Exit;
class Rocket;
class Wall;

class Visitor
{
    public:
        virtual ~Visitor(void);

        virtual void visitBonus(Bonus* e) = 0;
        virtual void visitCharacter(Character* e) = 0;
        virtual void visitExit(Exit* e) = 0;
        virtual void visitRocket(Rocket* e) = 0;
        virtual void visitWall(Wall* e) = 0;

    protected:
        Visitor(void);

};

#endif // VISITOR_H
