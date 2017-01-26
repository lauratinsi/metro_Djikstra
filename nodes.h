//
// Created by Laura TINSI on 26/12/2016.
//
#include <iostream>
#include <list>
#include <vector>

using namespace std;
#ifndef METRO_2_NODES_H
#define METRO_2_NODES_H



class nodes {

private:
    // a node is composed of its name, a predecessor in a way of nodes, a distance to the beguining of a way of nodes,
    // a position in_out usefull when a node is part of a vecnodes.
    // in_out can takes the value 1 or 0 depending on if the node is in the vecnodes or not.
    int name;
    int predecessor;
    long distance;
    int in_out;

public:
    //constructor
    nodes (int, int, long, int);

    //Accessors
    int GetName();
    int GetAnte();
    long GetDistance();
    int GetPosition();

    // Setters
    void SetName(int);
    void SetDistance(long);
    void SetAnte(int);
    void SetPosition(int);

    // Function for equality between two nodes
    bool equals(nodes, nodes);


};


#endif