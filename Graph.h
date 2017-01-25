#pragma once

#include "Vertex.h"
#include <queue>
#include <stack>

using namespace std;

class Graph
{
private:
    vector<Vertex> vertices;
public:
    Graph();
    Graph(vector<Vertex>);
    Graph(const Graph& graph)
    {
        this->vertices = vertices;
    }
    void addEdge(int,int);
    void addEdgeVertex(Vertex&,Vertex&);
    void addVertex(const Vertex&);
    vector<Vertex> getVertices() const;
    vector<Vertex* > getNeighbors(int i) const
    {
        return this->vertices[i].neighbors;
    }
    void normalize()
    {
        for(size_t i = 0; i < this->vertices.size(); i++)
        {
            for(size_t j = 0; j < this->vertices[i].neighbors.size(); j++)
            {
//                this->vertices[i].neighbors[j].neighbors = this->getVertex(this->vertices[i].neighbors[j]).neighbors;
            }
        }
    }
    Vertex getVertex(const Position&) const;
    Vertex getVertex(const Vertex& vertex)
    {
        for(size_t i = 0; i < vertices.size(); i++)
        {
            if(this->vertices[i] == vertex)
            {
                return this->vertices[i];
            }
        }

        return Vertex();
    }
    void allPathsHelp(Vertex& start, Vertex& end, vector< Vertex > path,vector< vector<Vertex> >&);
    vector<vector<Vertex> > allPaths(Vertex s, Vertex d);
    void setMarked(const Position&);
    void setFurnitures();
    void setPaintable();

};
