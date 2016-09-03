#ifndef VISITORBONUS_H
#define VISITORBONUS_H

#include "VisitorDoodad.h"

#include "Bonus.h"
#include "Character.h"
#include "Exit.h"
#include "Rocket.h"
#include "Wall.h"

class VisitorBonus : public VisitorDoodad<Bonus>
{
public:
    VisitorBonus(Bonus* bonus);
	VisitorBonus(void);

	virtual void visitBonus(Bonus* e);
	virtual void visitCharacter(Character* e);
	virtual void visitExit(Exit* e);
	virtual void visitRocket(Rocket* e);
	virtual void visitWall(Wall* e);
};

#endif // VISITORBONUS_H
