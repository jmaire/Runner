#ifndef VISITORROCKET_H
#define VISITORROCKET_H

#include "VisitorDoodad.h"

#include "Bonus.h"
#include "Character.h"
#include "Exit.h"
#include "Rocket.h"
#include "Wall.h"

class VisitorRocket : public VisitorDoodad<Rocket>
{
    public:
        VisitorRocket(Rocket* rocket);
        VisitorRocket(void);

        virtual ~VisitorRocket(void);

        virtual void visitBonus(Bonus* e) {};
        virtual void visitCharacter(Character* e);
        virtual void visitExit(Exit* e) {};
        virtual void visitRocket(Rocket* e);
        virtual void visitWall(Wall* e);
};

#endif // VISITORROCKET_H
