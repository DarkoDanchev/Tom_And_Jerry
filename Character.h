#include "Object.h"

class Character : public Object
{
private:

public:
    Character();
    Character(string,int,int);
    Character(const Character&);
    Character& operator=(const Character&);
    string getName() const;
    void setName(string);
    int getID() const;
    virtual Character* clone() const
    {
        return new Character(*this);
    }
    ~Character();



};
