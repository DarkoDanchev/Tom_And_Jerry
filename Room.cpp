#include "Room.h"

Room::Room()
{
    this->widght = 0;
    this->height = 0;
    this->positions = new Position*[0];
    this->positions[0] = new Position[0];
    this->Tom_Drone = Drone();
}

void Room::copy(const Room& room)
{
    this->widght = room.widght;
    this->height = room.height;
    this->positions = new Position*[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->positions[i] = new Position[widght];
    }
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->widght; j++)
        {
            this->positions[i][j] = room.positions[i][j];
        }
    }
    this->Tom_Drone = room.Tom_Drone;
}
void Room::erase()
{
    for(int i = 0; i < this->height; i++)
    {
        delete [] this->positions[i];
    }

    delete [] this->positions;
}
Room::Room(const Room& room)
{
    this->copy(room);
}
Room& Room::operator=(const Room& room)
{
    if(this != &room)
    {
        this->erase();
        this->copy(room);
    }

    return *this;
}
Room::Room(int widght,int height)
{
    this->widght = widght;
    this->height = height;

    this->positions = new Position*[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->positions[i] = new Position[this->widght];
    }

    this->Tom_Drone = Drone();
}
Room::Room(int widght,int height,Position** positions)
{
    this->widght = widght;
    this->height = height;

    this->positions = new Position*[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->positions[i] = new Position[this->widght];
    }

    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->widght; j++)
        {
            this->positions[i][j] = positions[i][j];
        }
    }

    this->Tom_Drone = Drone();
}

Room::Room(int widght,int height,Drone drone)
{
    this->widght = widght;
    this->height = height;

    this->positions = new Position*[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->positions[i] = new Position[this->widght];
    }

    this->Tom_Drone = drone;
}
Room::Room(int widght,int height,Drone drone,Position** positions)
{
    this->widght = widght;
    this->height = height;

    this->positions = new Position*[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->positions[i] = new Position[this->widght];
    }

    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->widght; j++)
        {
            this->positions[i][j] = positions[i][j];
        }
    }

    this->Tom_Drone = drone;
}
void Room::addFurniture(int x,int y,Furniture furniture)
{
    this->positions[x][y].setFurniture(furniture);
}
void Room::setPaintable(int x,int y,bool paintable)
{
    this->positions[x][y].setPaintable(paintable);
}

//--------------------the Drone commands-----------------------------
void Room::Forward()
{
    if(this->positions[this->Tom_Drone.getPosition().getX() + 1][this->Tom_Drone.getPosition().getY()].isAvalible())
    {
        Position newPosition = Position(this->Tom_Drone.getPosition().getX() + 1,this->Tom_Drone.getPosition().getY());
        this->Tom_Drone.setPosition(newPosition);
    }
}
void Room::Backward()
{
    if(this->positions[this->Tom_Drone.getPosition().getX() - 1][this->Tom_Drone.getPosition().getY()].isAvalible())
    {
        Position newPosition = Position(this->Tom_Drone.getPosition().getX() - 1,this->Tom_Drone.getPosition().getY());
        this->Tom_Drone.setPosition(newPosition);
    }
}
void Room::Right()
{
    if(this->positions[this->Tom_Drone.getPosition().getX()][this->Tom_Drone.getPosition().getY() + 1].isAvalible())
    {
        Position newPosition = Position(this->Tom_Drone.getPosition().getX(),this->Tom_Drone.getPosition().getY() + 1);
        this->Tom_Drone.setPosition(newPosition);
    }
}
void Room::Left()
{
    if(this->positions[this->Tom_Drone.getPosition().getX()][this->Tom_Drone.getPosition().getY() - 1].isAvalible())
    {
        Position newPosition = Position(this->Tom_Drone.getPosition().getX(),this->Tom_Drone.getPosition().getY() - 1);
        this->Tom_Drone.setPosition(newPosition);
    }
}
//-------------------------------------------------------------------

Position** Room::getPositions() const
{
    return this->positions;
}


Room::~Room()
{
    this->erase();
}
