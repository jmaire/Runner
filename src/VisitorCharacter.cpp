#include "VisitorCharacter.h"

VisitorCharacter::VisitorCharacter(Character* character)
: VisitorDoodad<Character>(character)
{}

VisitorCharacter::VisitorCharacter(void)
: VisitorCharacter(nullptr)
{}

void VisitorCharacter::visitBonus(Bonus* e)
{}

void VisitorCharacter::visitCharacter(Character* e)
{}

void VisitorCharacter::visitExit(Exit* e)
{}

void VisitorCharacter::visitRocket(Rocket* r)
{}

void VisitorCharacter::visitWall(Wall* e)
{}

