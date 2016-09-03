#include "Manifold.h"
#include "VisitorWall.h"

VisitorWall::VisitorWall(Wall* wall)
: VisitorDoodad<Wall>(wall)
{}

VisitorWall::VisitorWall()
: VisitorWall(nullptr)
{}

VisitorWall::~VisitorWall()
{}

void VisitorWall::visitBonus(Bonus* e)
{}

void VisitorWall::visitCharacter(Character* e)
{
	Manifold mf = Manifold(m_doodad->getBody(), e->getBody());
	mf.applyImpulse();
	mf.positionalCorrection();

	if(m_doodad->isDoodadOn(*e))
        e->setRun(true);

	if(m_doodad->isDoodadOnLeft(*e))
        e->setDead(true);
}

void VisitorWall::visitExit(Exit* e)
{}

void VisitorWall::visitRocket(Rocket* e)
{
    if(e->isExploding())
    {
        if(m_doodad->isDestructible())
        {
            m_doodad->toDestroy(true);
            m_doodad->createDebris();
        }
    }
    else
        e->explode();
}

void VisitorWall::visitWall(Wall* e)
{}

