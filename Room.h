#pragma once

#include "Drone.h"

#include "Furniture.h"

class Room
{
private:
    int widght,height;
    Position** positions; //this is two dimensional array of positions
    Drone Tom_Drone;
    void copy(const Room&);
    void erase();
public:
    Room();
    Room(int,int);
    Room(int,int,Position**);
    Room(int,int,Drone);
    Room(int,int,Drone,Position**);
    Room(const Room&);
    Room& operator=(const Room&);
    void addFurniture(int,int,Furniture);
    void setPaintable(int,int,bool);
    void Forward();
    void Backward();
    void Right();
    void Left();

    Position** getPositions() const;
    Drone getDrone() const;
    int getWidght() const;
    int getHeight() const;

    ~Room();

};
