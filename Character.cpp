#include "Character.h"


Character::Character() : Object()
{

}

Character::Character(string type,int x,int y) : Object(type,x,y)
{

}
Character::Character(const Character& ct) : Object(ct)
{

}
Character& Character::operator=(const Character& ct)
{
    if(this != &ct)
    {
        Object::operator=(ct);

    }

	return *this;
}

//the getters
string Character::getName() const
{
    return this->type;
}
//the setters
void Character::setName(string name)
{
    this->type = name;
}

int Character::getID() const
{
    return 1;
}
Character::~Character()
{

}
