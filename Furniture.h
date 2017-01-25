#pragma once

#include "Object.h"


class Furniture : public Object
{
private:

public:
    Furniture();
    Furniture(string,int,int);
    Furniture(const Furniture&);
    Furniture& operator=(const Furniture&);
    string getDescription() const;
    void setDescription(string);
    int getID() const;
    Furniture* clone() const
    {
        return new Furniture(*this);
    }
    ~Furniture();

};
