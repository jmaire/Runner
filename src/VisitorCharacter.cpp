#include "Manifold.h"
#include "VisitorCharacter.h"

VisitorCharacter::VisitorCharacter(Character* character)
: VisitorDoodad<Character>(character)
{}

VisitorCharacter::VisitorCharacter()
: VisitorCharacter(nullptr)
{}

VisitorCharacter::~VisitorCharacter()
{}

void VisitorCharacter::visitBonus(Bonus* e)
{
    e->setTaken(true);
}

void VisitorCharacter::visitExit(Exit* e)
{
    e->setReached(true);
}

void VisitorCharacter::visitWall(Wall* e)
{
	Manifold mf = Manifold(m_doodad->getBody(), e->getBody());
	mf.applyImpulse();
	mf.positionalCorrection();

	if(e->isDoodadOn(*m_doodad))
        m_doodad->setRun(true);

	if(e->isDoodadOnLeft(*m_doodad))
        m_doodad->setDead(true);
}

