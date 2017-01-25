#pragma once

#include <iostream>

#include "Node.h"
#include "Vertex.h"

#include <vector>

#include <fstream>

using namespace std;

class binary_tree
{
public:
    Node* root;
public:
    binary_tree();
    binary_tree(Node* root);
    void insert(Node*& node,string);
    void insert(string);
    void build_tree(vector< vector<Vertex> > paths,Node*& node);
    void build_tree(vector< vector<Vertex> > paths);
    void to_dot(Node* node,ofstream& file);
    void to_dot(ofstream& file);
    void index(Node* node,int index);
    void index();
};
binary_tree::binary_tree()
{
    this->root = nullptr;
}
binary_tree::binary_tree(Node* root)
{
    this->root = root;
}
void binary_tree::insert(Node*& node,string data)
{
    Node* inserted = new Node(data,nullptr,nullptr);
    if(node == nullptr)
    {
        node = new Node(inserted->data,nullptr,nullptr);

        //cout<<"Inserting root";

    }
    else
    {
        //cout<<"Else"<<endl;
        if(node->left == nullptr)
        {
            node->left = new Node(inserted->data,nullptr,nullptr);
        }
        else if(node->right == nullptr)
        {
            node->right = new Node(inserted->data,nullptr,nullptr);
        }
        else
        {
                return; //cant insert on this node;
        }
    }
}
void binary_tree::insert(string data)
{
    //cout<<"Insert root"<<endl;
    this->insert(this->root,data);
}
void binary_tree::build_tree(vector< vector<Vertex> > paths, Node*& node)
{
    if(paths.size() <= 1)
    {
        return;
    }

    this->insert(node,paths[0][0].TAG);

    for(size_t i = 1; i < paths.size(); i++)
    {
        if(paths[i][0].TAG != paths[0][0].TAG)
        {
            this->insert(node,paths[i][0].TAG);
            break;
        }
    }
    if(node->right == nullptr)
    {
        for(size_t i = 0; i < paths.size(); i++)
        {
            paths[i].erase(paths[i].begin());
        }
        this->build_tree(paths,node->left);
    }
    else
    {
        vector< vector<Vertex> > left,right;
        for(size_t i = 0; i < paths.size(); i++)
        {
            if(paths[i][0].TAG == node->left->data)
            {
                paths[i].erase(paths[i].begin());
                left.push_back(paths[i]);
            }
            else
            {
                paths[i].erase(paths[i].begin());
                right.push_back(paths[i]);
                //cout<<"Inserting right"<<endl;
            }
        }
        //cout<<"Left size: "<<right.size()<<endl;
        this->build_tree(left,node->left);
        this->build_tree(right,node->right);
    }


}
void binary_tree::build_tree(vector< vector<Vertex> > paths)
{
    this->insert("START");

    this->build_tree(paths,this->root);
}
void binary_tree::to_dot(Node* node,ofstream& file)
{
    if(node->left == nullptr && node->right == nullptr)
    {
        return;
    }
    else if(node->left != nullptr && node->right == nullptr)
    {
        file<<node->id << "[label=" + node->data + "];\n";
        file<<node->left->id << "[label=" + node->left->data + "];\n";
        file<<node->id << " -> " << node->left->id << "\n";
        to_dot(node->left,file);
    }
    else if(node->left == nullptr && node->right != nullptr)
    {
        file<<node->id << "[label=" + node->data + "];\n";
        file<<node->right->id << "[label=" + node->right->data + "];\n";
        file<<node->id << " -> " << node->right->id << "\n";
        to_dot(node->right,file);
    }
    else
    {
        file<<node->id << "[label=" + node->data + "];\n";
        file<<node->left->id << "[label=" + node->left->data + "];\n";
        file<<node->id << " -> " << node->left->id << "\n";
        //file<<node->id << "[label=" + node->data + "];\n";
        file<<node->right->id << "[label=" + node->right->data + "];\n";
        file<<node->id << " -> " << node->right->id << "\n";

        to_dot(node->left,file);
        to_dot(node->right,file);
    }
}
void binary_tree::to_dot(ofstream& file)
{
    this->index();
    file<<"digraph G{\n";
    this->to_dot(this->root,file);
    file<<"}";
}
void binary_tree::index(Node* node,int index)
{
    node->id = index;
    if(node->left == nullptr && node->right == nullptr)
    {
        return;
    }
    else if(node->left != nullptr && node->right == nullptr)
    {

        this->index(node->left,index + 1);
    }
    else if(node->left == nullptr && node->right != nullptr)
    {

        this->index(node->right,index + 1);
    }
    else
    {

        this->index(node->left,index + 1);
        this->index(node->right,index + 2);
    }
}
void binary_tree::index()
{
    this->index(this->root,0);
}
