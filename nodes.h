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
    std::list<int> path;
    int distance;
    static long _infinity;
    static int const _size;

public:

    int GetName();
    std::list<int> Getpath();
    int GetDistance();
    long GetInfinity();

    void SetName(int);
    void SetDistance(int);
    void SetPath(nodes);
    bool equals(nodes, nodes);
    void NewDist(nodes, nodes, vector< vector<int> > G);
    nodes FindMin(vector< vector<int> > M);

};


#endif
