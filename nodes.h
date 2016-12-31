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
    //static int const _size;

public:
    nodes (int, int, long);
    int GetName();
    int GetAnte();
    long GetDistance();

    void SetName(int);
    void SetDistance(long);
    void SetAnte(int);
    bool equals(nodes, nodes);
    //static void NewDist(nodes, nodes, vector< vector<long> > G);


};


#endif
