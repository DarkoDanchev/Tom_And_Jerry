#include "Drone.h"


Drone::Drone()
{
    this->owner = "";
    this->position = Position();
} //the default constructor

Drone::Drone(string owner,Position position)
{
    this->owner = owner;
    this->position = position;
}
Drone::Drone(const Drone& dr)
{
    this->owner = dr.owner;
    this->position = dr.position;
}

Drone& Drone::operator=(const Drone& dr)
{
    if(this != &dr)
    {
        this->owner = dr.owner;
        this->position = dr.position;
    }

    return *this;
}

string Drone::getOwner() const
{
    return this->owner;
}
void Drone::setOwner(const string& owner)
{
    this->owner = owner;
}


//the drone moving functions
void Drone::Forward()
{
    int y = this->position.getY() + 1;
    this->position.setY(y);
}
void Drone::Backward()
{
    int y = this->position.getY() - 1;
    this->position.setY(y);
}
void Drone::Right()
{
    int x = this->position.getX() + 1;
    this->position.setX(x);
}
void Drone::Left()
{
    int x = this->position.getX() - 1;
    this->position.setX(x);
}
Drone::~Drone()
{
    this->owner = "";
}
