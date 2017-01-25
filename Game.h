#include <iostream>
#include <vector>
#include <fstream>

#include "Object.h" //for testing

#include "Character.h"
#include "Drone.h"
#include "Position.h"
#include "Room.h"
#include "Vertex.h"
#include "Graph.h"
#include "binary_tree.h"

using namespace std;

class Game
{

public:
    Game();
    Graph build_graph(Position**,int widght,int height);
    int shortest_path(Graph,Vertex first,Vertex second);
    int all_shortest_paths(Graph,Vertex,Vertex);
    int total_paint_amount(Graph,Vertex,Vertex);
    vector<int> all_turns(Graph,Vertex,Vertex);
    vector<int> paint_amount(Graph,Vertex,Vertex);
    vector< vector<Vertex> > get_shortest_paths(Graph,Vertex,Vertex);
    void tag_shortest_paths(vector< vector<Vertex> >& paths);
    int bonus_two(Graph,Vertex,Vertex); //returns index of a path
    int paint_amount(vector< Vertex > path);
    int bonus_three(Graph,Vertex,Vertex); //returns amount

};

Game::Game()
{
    ifstream program("program.txt");

    int roomHeight,roomWidght;
    program>>roomWidght>>roomHeight;
    Position** positions = new Position*[roomHeight];
    for(int i = 0; i < roomHeight; i++)
    {
        positions[i] = new Position[roomWidght];
    }

    //setting up the default positions
    for(int i = 0; i < roomHeight; i++)
    {
        for(int j = 0; j < roomWidght; j++)
        {
            positions[i][j] = Position(i,j);
        }
    }

    int jerryX,jerryY;
    program>>jerryX>>jerryY;
    Character Jerry = Character("Jerry",jerryX,jerryY);

    int tomX,tomY;
    program>>tomX>>tomY;
    Character Tom = Character("Tom",tomX,tomY);

    //the Drone Object
    Position droneSpawn = Position(Tom.getX(),Tom.getY());
    Drone drone = Drone("Tom",droneSpawn);




    int furnitures_positions,painting_positions;
    program>>furnitures_positions>>painting_positions;

    Furniture f("a",0,0);
//    Object* ob = new Furniture("a",0,0);

//    positons[0][0] = Position(ob);

    //cout<<ob->getID();

    //cout<<furnitures_positions<<endl;


    vector<string> furnitures_descriptions;
    Furniture* furnitures = new Furniture[furnitures_positions];

    for(int i = 0; i < furnitures_positions; i++)
    {
        string description = "";
        string line;
        /*
            Because of a bug in the C++ file reading system when it reads the first furniture for some
            reason is reading a empty string we have to check when we are reading the first furiniture
            and manualy remove the empty line.
            THERE IS NO OTHER SOLUTION TO THIS BUG.
        */

        //getline(program,line);

        int x,y;
        program>>x>>y;

        while(line != "===")
        {
            getline(program,line);
            description += line + "\n";
        }
        //description += "===";
        furnitures_descriptions.push_back(description);
        furnitures[i] = Furniture(furnitures_descriptions[i],x,y);
        positions[x][y] = Position(x,y,furnitures[i]);
    }
    //cout<<furnitures_descriptions[2]<<endl;

    int paintX,paintY;
    for(int i = 0; i < painting_positions; i++)
    {
        program>>paintX>>paintY;
        positions[paintX][paintY].setPaintable(true);
    }

    //creating the room
    Room room = Room(roomWidght,roomHeight,drone,positions);

    //cout<<room.getPositions()[1][0].isPaintable()<<endl;

    Graph graph = this->build_graph(positions,roomWidght,roomHeight);

    Vertex vertex;
    vertex.neighbors = graph.getVertices()[0].neighbors;
   // cout<<"Neighbors: "<<graph.getVertices()[0].neighbors[0]->neighbors.size()<<endl;
    //graph.BFS(0,2);
    //cout<<shortest_path(graph,graph.getVertices()[0],graph.getVertices()[6]);

    //cout<<"===================================="<<endl;

    graph.setFurnitures();
    graph.setPaintable();

    Vertex start = graph.getVertex(positions[tomX][tomY]);

    Vertex end = graph.getVertex(positions[jerryX][jerryY]);

    int tomIndex = 0,jerryIndex = 0;
    for(size_t i = 0; i < graph.getVertices().size(); i++)
    {
        if(graph.getVertices()[i].position == positions[Tom.getX()][Tom.getY()])
        {
            tomIndex = i;
            cout<<"Tom Index="<<tomIndex<<endl;
        }
        if(graph.getVertices()[i].position == positions[Jerry.getX()][Jerry.getY()])
        {
            jerryIndex = i;
        }
    }

    binary_tree tree;

    vector< vector<Vertex> > shorth = this->get_shortest_paths(graph,graph.getVertices()[tomIndex],graph.getVertices()[jerryIndex]);

    //cout<<shorth.size()<<endl;
    this->tag_shortest_paths(shorth);

    tree.build_tree(shorth);



    ofstream file("tree.gv");

    tree.to_dot(file);

    int index;
    cout<<"Enter shortest path index [from 0 to " <<shorth.size()-1<<"]:";
    cin>>index;

    cout<<"Paint amount: "<<this->paint_amount(shorth[index])<<endl;
    cout<<"Bonus 2: "<<this->bonus_two(graph,graph.getVertices()[tomIndex],graph.getVertices()[jerryIndex])<<endl;
    cout<<"Bonus 3: "<<this->bonus_three(graph,graph.getVertices()[tomIndex],graph.getVertices()[jerryIndex])<<endl;





}
Graph Game::build_graph(Position** positions,int widght,int height)
{
    Graph graph;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < widght; j++)
        {
            Vertex vertex = Vertex(positions[i][j],false);
            graph.addVertex(vertex);
        }
    }


    int times = 1;
    for(size_t i = 0; i < graph.getVertices().size(); i++)
    {
        if((int)i % (((times*widght) - 1)) == 0)
        {
            if(i != 0)
            {
                times++;
                //cout<<"True for i: "<<i<<endl;
                continue;
            }



        }
        graph.addEdge(i,i+1);
        //graph.addEdgeVertex(graph.getVertices()[i],graph.getVertices()[i+1]);
    }
    for(size_t i = 0; i < graph.getVertices().size(); i++)
    {
        if((int)i > ((widght*height) - 1) - widght)
            break;
        graph.addEdge(i,i+widght);
        //graph.addEdgeVertex(graph.getVertices()[i],graph.getVertices()[i+widght]);
    }

    //Graph gr(graph.getVertices());



    return graph;
}
int Game::shortest_path(Graph graph,Vertex first,Vertex second)
{
    vector< vector<Vertex> > all = graph.allPaths(first,second);

    //cout<<all.size()<<endl;

    int length = 100000000;

    for(size_t i = 0; i < all.size(); i++)
    {
        if((size_t)length > all[i].size())
        {
        length = all[i].size();
       // cout<<all[i].size()<<endl;
        }
    }

    return length-1;
}
int Game::all_shortest_paths(Graph graph,Vertex first,Vertex second)
{
    vector< vector<Vertex> > all = graph.allPaths(first,second);

    int length = this->shortest_path(graph,first,second);

    int paths = 0;
    for(size_t i = 0; i < all.size(); i++)
    {
        if((size_t)length == all[i].size()-1)
        {
            paths++;
        }
    }

    return paths;

}
int Game::total_paint_amount(Graph graph,Vertex first,Vertex second)
{
    vector< vector<Vertex> > all = graph.allPaths(first,second);
    int paint = 0;
    for(size_t i = 0; i < all.size(); i++)
    {
        for(size_t j = 0; j < all[i].size(); j++)
        if(all[i][j].paintable)
        {
            paint++;
        }
    }

    return paint;

}
vector<int> Game::paint_amount(Graph graph,Vertex first,Vertex second)
{
    vector< vector<Vertex> > all = graph.allPaths(first,second);

    vector<int> amount;

    int paint;
    for(size_t i = 0; i < all.size(); i++)
    {
        paint = 0;
        for(size_t j = 0; j < all[i].size(); j++)
        {
            if(all[i][j].paintable)
            {
                paint++;
            }
        }
        amount.push_back(paint);
    }

    return amount;
}
vector<int> Game::all_turns(Graph graph,Vertex first,Vertex second)
{
    vector< vector<Vertex> > all = graph.allPaths(first,second);

    vector<int> turns;

    int turn;

    for(size_t i = 0; i < all.size(); i++)
    {
        turn = 0;
        for(size_t j = 1; j < all[i].size()-1; j++)
        {
            if(all[i][j-1].position.getX() != all[i][j+1].position.getX() || all[i][j-1].position.getY() != all[i][j+1].position.getY())
            {

                turn++;
            }
        }
        turns.push_back(turn);
    }

    return turns;

}
vector< vector<Vertex> > Game::get_shortest_paths(Graph graph,Vertex start,Vertex end)
{
    vector< vector<Vertex> > all = graph.allPaths(start,end);

    int shortesth = this->shortest_path(graph,start,end);



    vector< vector<Vertex> > paths;

    for(size_t i = 0; i < all.size(); i++)
    {
        if(all[i].size() == (size_t)shortesth + 1)
        {
            paths.push_back(all[i]);
        }
    }

    return paths;
}
void Game::tag_shortest_paths(vector<vector<Vertex> >& paths)
{
    for(size_t i = 0; i < paths.size(); i++)
    {
        for(size_t j = 0; j < paths[i].size()-1; j++)
        {
            if(paths[i][j+1].position.getX() == paths[i][j].position.getX() + 1)
            {
                paths[i][j].TAG = "F";
            }
            else if(paths[i][j+1].position.getX() == paths[i][j].position.getX() - 1)
            {
                paths[i][j].TAG = "B";
               // cout<<"In back"<<endl;
            }
            else if(paths[i][j+1].position.getY() == paths[i][j].position.getY() - 1)
            {
                paths[i][j].TAG = "L";
               // cout<<"In left"<<endl;
            }
            else
            {
                paths[i][j].TAG = "R";
            }
        }
    }
}
int Game::bonus_two(Graph graph,Vertex first,Vertex second)
{
    vector<int> paint = this->paint_amount(graph,first,second);

    int max_paint = 0;
    for(size_t i = 0; i < paint.size(); i++)
    {
        if(max_paint < paint[i])
            max_paint = paint[i];
    }

    int index = 0;



    vector<int> turns = this->all_turns(graph,first,second);

    int turn = turns[0];

    for(size_t i = 0; i < turns.size(); i++)
    {
        if(max_paint == paint[i] && turns[i] < turn)
            index = i;
    }

    return index;
}
int Game::paint_amount(vector< Vertex > path)
{
    int paint = 0;
    for(size_t i = 0; i < path.size(); i++)
    {
        if(path[i].paintable)
            paint++;
    }

    return paint;
}
int Game::bonus_three(Graph graph,Vertex first,Vertex second)
{
    vector< vector<Vertex> > paths = this->get_shortest_paths(graph,first,second);

    int max_paint = 0,max_paint2 = 0;
    int index = 0;
    for(size_t i = 0; i < paths.size(); i++)
    {
        if(this->paint_amount(paths[i]) > max_paint)
        {
            max_paint = this->paint_amount(paths[i]);
            index = i;
        }
    }
    for(size_t i = 0; i < paths.size(); i++)
    {
        if(this->paint_amount(paths[i]) > max_paint2 && i != index)
            max_paint2 = this->paint_amount(paths[i]);
    }

    return max_paint2 + max_paint;
}

