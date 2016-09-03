#ifndef VISITORWALL_H
#define VISITORWALL_H

#include "VisitorDoodad.h"

#include "Bonus.h"
#include "Character.h"
#include "Exit.h"
#include "Rocket.h"
#include "Wall.h"

class VisitorWall : public VisitorDoodad<Wall>
{
    public:
        VisitorWall(Wall* wall);
        VisitorWall(void);

        virtual ~VisitorWall(void);

        virtual void visitBonus(Bonus* e);
        virtual void visitCharacter(Character* e);
        virtual void visitExit(Exit* e);
        virtual void visitRocket(Rocket* e);
        virtual void visitWall(Wall* e);
};

#endif // VISITORWALL_H
