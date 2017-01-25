#pragma once

#include "Position.h"

class Drone
{
private:
    string owner;
    Position position;
public:
    Drone();
    Drone(string,Position);
    Drone(const Drone&);
    Drone& operator=(const Drone&);
    string getOwner() const;
    Position getPosition() const
    {
        return this->position;
    }
    void setOwner(const string&);
    void setPosition(Position position)
    {
        this->position = position;
    }
    void Forward();
    void Backward();
    void Right();
    void Left();
    ~Drone();

};
