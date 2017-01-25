#include "Furniture.h"

Furniture::Furniture() : Object()
{

}
Furniture::Furniture(string type,int x,int y) : Object(type,x,y)
{

}
Furniture::Furniture(const Furniture& ft) : Object(ft)
{

}
Furniture& Furniture::operator=(const Furniture& ft)
{
    if(this != &ft)
    {
        Object::operator=(ft);

    }

    return *this;
}

//the getters
string Furniture::getDescription() const
{
    return this->type;
}
int Furniture::getID() const
{
    return 0;
}
//the setters
void Furniture::setDescription(string type)
{
    this->type = type;
}
Furniture::~Furniture()
{

}
