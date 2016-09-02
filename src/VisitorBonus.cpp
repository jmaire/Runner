#include "VisitorBonus.h"

VisitorBonus::VisitorBonus(Bonus* bonus)
: VisitorDoodad<Bonus>(bonus)
{}

VisitorBonus::VisitorBonus()
: VisitorBonus(nullptr)
{}

void VisitorBonus::visitBonus(Bonus* e)
{}

void VisitorBonus::visitCharacter(Character* e)
{
	m_doodad->setTaken(true);
}

void VisitorBonus::visitExit(Exit* e)
{}

void VisitorBonus::visitRocket(Rocket* r)
{}

void VisitorBonus::visitWall(Wall* e)
{}

