#pragma once

#include "Position.h"

#include <vector>

struct Vertex
{
    Position position;
    vector<Vertex* > neighbors;

    bool marked;

    bool paintable;

    string TAG;

    Vertex()
    {
        position = Position();
        neighbors = vector<Vertex* >(0);
        marked = false;
        paintable = false;
        TAG = "";
    }

    vector<Vertex* > getNeighbors()
    {
        return neighbors;
    }
    Vertex(Position ps,bool md)
    {
        position = ps;
        marked = md;
        paintable = false;
        TAG = "";
    }

    Vertex(Position ps,vector<Vertex* > nbs,bool md)
    {
        position = ps;
        neighbors = nbs;
        marked = md;
        paintable = false;
        TAG = "";
    }
    bool operator==(const Vertex& vertex)
    {
        return position == vertex.position;
    }
    bool operator!=(const Vertex& vertex)
    {
        return position.getX() != vertex.position.getX() && position.getY() != vertex.position.getY() ;
    }
};

