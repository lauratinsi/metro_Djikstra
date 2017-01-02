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

class vecnodes {
private:
    vector< vector<long>> v;
public:
    void addvecnodes(nodes);
    vector< vector<long>> Getv();
    void Setv_predecessor(int i, int);
    void Setv_distance(int i, int);
    void Setv_position(int i, int);
    static vecnodes creation(vector<vector<long> > G);
    static nodes GetNodInVec(int, vecnodes T);
    static nodes FindMin(vecnodes M);
    //void delete_in_vec(int i);
    static void NewDist(nodes a, nodes b, vector< vector<long> > G, vecnodes* T);
    static bool NotEmpty(vecnodes* T);
    static vecnodes Djikstra(vector< vector<long> > G, nodes b);

};


#endif //METRO_2_VECNODES_H
