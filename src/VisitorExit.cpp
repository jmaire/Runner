#include "VisitorExit.h"

VisitorExit::VisitorExit(Exit* exit)
: VisitorDoodad<Exit>(exit)
{}

VisitorExit::VisitorExit()
: VisitorExit(nullptr)
{}

void VisitorExit::visitBonus(Bonus* e)
{}

void VisitorExit::visitCharacter(Character* e)
{
    e->getBody().setRectangle(sf::Vector2f(e->getBody().getRectangle().x-3,e->getBody().getRectangle().y-3));
    if(0 == e->getBody().getRectangle().x)
    {
    	e->setState(2);
    }
}

void VisitorExit::visitExit(Exit* e)
{}

void VisitorExit::visitRocket(Rocket* r)
{}

void VisitorExit::visitWall(Wall* e)
{}

