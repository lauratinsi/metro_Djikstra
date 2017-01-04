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

    int name;
    int predecessor;
    long distance;
    int in_out; //in vaut 1 ou vaut 0
    //static int const _size;

public:
    nodes (int, int, long, int);
    int GetName();
    int GetAnte();
    long GetDistance();
    int GetPosition();

    void SetName(int);
    void SetDistance(long);
    void SetAnte(int);
    void SetPosition(int);
    bool equals(nodes, nodes);


};


#endif
