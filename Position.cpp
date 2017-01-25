#include "Position.h"


Position::Position()
{
    this->x = 0;
    this->y = 0;
    this->furniture = Furniture();
    this->paintable = false;
}
Position::Position(int x,int y)
{
    this->x = x;
    this->y = y;
    this->furniture = Furniture();
    this->paintable = false;
    //assert(object != NULL);
}
Position::Position(int x,int y,Furniture furniture)
{
    this->x = x;
    this->y = y;
    this->furniture = furniture;
    this->paintable = false;
}
Position::Position(int x,int y,Furniture furniture,bool paintable)
{
    this->x = x;
    this->y = y;
    this->furniture = furniture;
    this->paintable = paintable;
}
Position::Position(const Position& p)
{
    this->x = p.x;
    this->y = p.y;
    this->furniture = p.furniture;
    this->paintable = p.paintable;
}
Position& Position::operator=(const Position& p)
{
    if(this != &p)
    {
//        delete this->furniture;
        this->x = p.x;
        this->y = p.y;
        this->furniture = p.furniture;
        this->paintable = p.paintable;
    }

    return *this;
}

//the getter for the object
Furniture Position::getFurniture() const
{
    return this->furniture;
}
bool Position::isAvalible() const
{
    return this->furniture.getDescription() == "";
}
bool Position::operator==(const Position& position) const
{
    return this->x == position.x && this->y == position.y;
}
int Position::getX() const
{
    return this->x;
}
int Position::getY() const
{

    return this->y;
}
void Position::setX(int x)
{
    this->x = x;
}
void Position::setY(int y)
{
    this->y = y;
}
void Position::setPaintable(bool paintable)
{
    this->paintable = paintable;
}
void Position::setFurniture(Furniture furniture)
{
    this->furniture = furniture;
}

bool Position::isPaintable() const
{
    return this->paintable;
}
//the destructor
Position::~Position()
{
//    delete this->furniture;
}
