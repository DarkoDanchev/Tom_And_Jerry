#include "Graph.h"

#include <iostream>


Graph::Graph()
{
    this->vertices = vector<Vertex>(0);
}
Graph::Graph(vector<Vertex> vertices)
{
    this->vertices = vertices;
}
void Graph::addEdge(int i,int j)
{
    this->vertices[i].neighbors.push_back(&this->vertices[j]);
    this->vertices[j].neighbors.push_back(&this->vertices[i]);

    /*this->vertices[i].neighbors[this->vertices[i].neighbors.size()-1].neighbors.push_back(this->vertices[i]);

    this->vertices[j].neighbors[this->vertices[j].neighbors.size()-1].neighbors.push_back(this->vertices[j]);

    cout<<"Adding edge between: "<<i<<" and "<<j<<endl;

    cout<<"size second: "<<this->vertices[i].neighbors[this->vertices[i].neighbors.size()-1].neighbors.size()<<endl;
    cout<<"size first: "<<this->vertices[j].neighbors[this->vertices[j].neighbors.size()-1].neighbors.size()<<endl;*/
}
void Graph::addEdgeVertex(Vertex& one,Vertex& two)
{
    one.neighbors.push_back(&two);
    two.neighbors.push_back(&one);
}
void Graph::addVertex(const Vertex& vertex)
{
    this->vertices.push_back(vertex);
}
vector<Vertex> Graph::getVertices() const
{
    return this->vertices;
}
Vertex Graph::getVertex(const Position& position) const
{
    for(size_t i = 0; i < this->vertices.size();i++)
    {
        if(this->vertices[i].position == position)
        {
            cout<<"Returning"<<endl;
            return this->vertices[i];
        }
    }

    Vertex empty;
    //cout<<"No such vertex";
    return empty;
}
void Graph::setFurnitures()
{
    for(size_t i = 0; i < this->vertices.size(); i++)
    {
        if(!this->vertices[i].position.isAvalible())
        {
            this->vertices[i].marked = true;
        }
    }
}
void Graph::setPaintable()
{
    for(size_t i = 0; i < this->vertices.size(); i++)
    {
        if(this->vertices[i].position.isPaintable())
        {
            this->vertices[i].paintable = true;
        }
    }
}

void Graph::setMarked(const Position& position)
{
    for(size_t i = 0; i < this->vertices.size();i++)
    {
        if(this->vertices[i].position == position)
            this->vertices[i].marked = true;
    }
}
void Graph::allPathsHelp(Vertex& start, Vertex& end, vector< Vertex > path,vector< vector<Vertex> >& all)
{
	//cout << start.position.getY() << endl;


//	s.push(start);
	path.push_back(start);

	//cout<<s.top().position.getY();


    if(start == end)
    {
        if(path.size() < 3)
        {
            all.push_back(path);

        }
        else if(path[0].position.getX() != path[2].position.getX() && path[0].position.getY() != path[2].position.getY())
        {
        /*for(int i = 0; i < path.size(); i++)
        {

            cout<<"("<<path[i].position.getX()<<","<<path[i].position.getY()<<") ";
        }
        cout<<endl;*/

        all.push_back(path);
        //if(path[0].position.getX() == path[2].position.getX())
            //all.pop_back();

        }
    }

    start.marked = true;

    for (size_t i = 0; i < start.neighbors.size(); i++) {


		if (start.neighbors[i]->marked == false)
		{
            //start.neighbors[i]->marked = true;
            //cout<<"Util for n: "<<i<<endl;
			allPathsHelp(*start.neighbors[i],end,path,all);
        }

	}


    path.pop_back();
    start.marked = false;
    //start.marked = false;

        // Mark the current node and store it in path[]



    // If current vertex is same as destination, then print
    // current path[]

}
vector<vector<Vertex> > Graph::allPaths(Vertex s, Vertex d)
{
    // Mark all the vertices as not visited


    // Create an array to store paths
    vector< Vertex > path;
    vector< vector<Vertex> > all;
//    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    // Call the recursive helper function to print all paths
    allPathsHelp(s, d, path,all);

    vector< vector<Vertex> >::iterator it = all.begin();

    for(size_t i = 0; i < all.size(); i++)
    {
        for(size_t j = 0; j < all[i].size();j++)
        {
            if(all[i][2] == all[i][0])
            {
                all.erase(all.begin() + i);
            }
        }
    }

    return all;
}
