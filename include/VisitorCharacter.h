#ifndef VISITORCHARACTER_H
#define VISITORCHARACTER_H

#include "VisitorDoodad.h"

#include "Bonus.h"
#include "Character.h"
#include "Exit.h"
#include "Rocket.h"
#include "Wall.h"

class VisitorCharacter : public VisitorDoodad<Character>
{
    public:
        VisitorCharacter(Character* character);
        VisitorCharacter(void);

        virtual ~VisitorCharacter(void);

        virtual void visitBonus(Bonus* e);
        virtual void visitCharacter(Character* e) {};
        virtual void visitExit(Exit* e);
        virtual void visitRocket(Rocket* e) {};
        virtual void visitWall(Wall* e);
};

#endif // VISITORCHARACTER_H
