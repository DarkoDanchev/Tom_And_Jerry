#pragma once

#include <cstring>
#include <string>

using namespace std;

class Object
{
protected:
    string type;
    //the position of the object
    int x , y;

public:
    Object();
    Object(string,int,int);
    Object(const Object&);
    Object& operator=(const Object&);
    string getType() const;
    int getX() const;
    int getY() const;
    void setType(string);
    void setX(int);
    void setY(int);
    void setPosition(int , int);
    virtual int getID() const = 0;
    virtual Object* clone() const = 0;

    virtual ~Object() = 0;
protected:
    void copy(const Object&);

};
