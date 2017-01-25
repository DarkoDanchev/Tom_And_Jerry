#include "Object.h"

Object::Object()
{
    this->type = "";

    this->x = -1;
    this->y = -1;
}
Object::Object(string type,int x,int y)
{
    this->type = type;
    this->x = x;
    this->y = y;
}
Object::Object(const Object& obj)
{
    this->copy(obj);
}
Object& Object::operator=(const Object& obj)
{
    if(this != &obj)
    {
        this->type = "";
        this->copy(obj);
    }

    return *this;
}
//the private copy function
void Object::copy(const Object& obj)
{
    this->type = obj.getType();
    this->x = obj.getX();
    this->y = obj.getY();
}

//the getters
string Object::getType() const
{
    return this->type;
}
int Object::getX() const
{
    return this->x;
}
int Object::getY() const
{
    return this->y;
}
int Object::getID() const
{
    return -1;
}
//the setters
void Object::setType(string type)
{
    this->type = type;
}
void Object::setX(int x)
{
    this->x = x;
}
void Object::setY(int y)
{
    this->y = y;
}
void Object::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

//the destructor
Object::~Object()
{
    this->type = "";
}
