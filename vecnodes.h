//
// Created by Laura TINSI on 29/12/2016.
//
#include <iostream>
#include "nodes.h"
#include <list>
#include <vector>
#ifndef METRO_2_VECNODES_H
#define METRO_2_VECNODES_H
using namespace std;

// A vecnodes is a vector of nodes.
// Comments about the functions are made in the .cpp

class vecnodes {

private:
    vector< vector<long>> v;
public:

    //Constructor
    vector< vector<long>> Getv();

    //Setters
    void Setv_predecessor(int i, int p);
    void Setv_distance(int i, int d);
    void Setv_position(int i, int);

    //Functions
    void addvecnodes(nodes);
    static vecnodes creation(vector<vector<long> > G);
    static nodes GetNodInVec(int, vecnodes T);
    static nodes FindMin(vecnodes M);
    static void NewDist(nodes a, nodes b, vector< vector<long> > G, vecnodes* T);
    static bool NotEmpty(vecnodes* T);

    //Main function
    static vector<int> Djikstra(vector< vector<long> > G, nodes b, nodes a);

};

#endif //METRO_2_VECNODES_H