#pragma once

struct Node
{
    string data;
    Node* left;
    Node* right;

    int id;

    Node(string dt,Node* lt,Node* rt)
    {
        data = dt;
        left = lt;
        right = rt;

    }
};
