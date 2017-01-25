#pragma once

#include "Furniture.h"

using namespace std;

class Position
{
private:
    int x,y;
    Furniture furniture;
    bool paintable;
public:
    Position();
    Position(int x,int y);
    Position(int x,int y,Furniture);
    Position(int x,int y,Furniture,bool);
    void setPaintable(bool);
    void setFurniture(Furniture furniture);
    bool isPaintable() const;
    Position(const Position&);
    Position& operator=(const Position&);
    bool isAvalible() const;
    bool operator==(const Position&) const;
    int getX() const;
    int getY() const;
    void setX(int);
    void setY(int);
    Furniture getFurniture() const;
    ~Position();
};
