#ifndef VISITOREXIT_H
#define VISITOREXIT_H

#include "VisitorDoodad.h"

#include "Bonus.h"
#include "Character.h"
#include "Exit.h"
#include "Rocket.h"
#include "Wall.h"

class VisitorExit : public VisitorDoodad<Exit>
{
public:
    VisitorExit(Exit* exit);
	VisitorExit(void);

	virtual void visitBonus(Bonus* e);
	virtual void visitCharacter(Character* e);
	virtual void visitExit(Exit* e);
	virtual void visitRocket(Rocket* e);
	virtual void visitWall(Wall* e);
};

#endif // VISITOREXIT_H
