//
// Created by Laura TINSI on 29/12/2016.
//GTFS format regarder documentation google sur git ou sof pour les données RATP ou data.ratp.fr mes creations
#include <iostream>
#include "nodes.h"
#include <list>
#include <vector>
#include "vecnodes.h"
long infinity= 10000000000000;
using namespace std;


// Adds a node at the end of the vecnodes
void vecnodes::addvecnodes(nodes n) {
    v.push_back({n.GetName(),n.GetAnte(),n.GetDistance(),n.GetPosition()});
}

// Returns the vecnodes as a vector< vector<long> >. Each vector<long> is a node.
vector< vector<long>> vecnodes::Getv(){
    return v;
}

// sets p as the predecessor of i
void vecnodes::Setv_predecessor(int i, int p){
    v[i][1]= p;
}

// Sets the distance d between i and the initial node.
void vecnodes::Setv_distance(int i, int d){
    v[i][2]= d;
}

// The position of a node i in a vecnodes can be 0 or 1. This is a way of  considering the node is actually in the
// vecnodes or not. If p = 0 then the node appear as not being part of the vecnodes.
void vecnodes::Setv_position(int i, int p) {
    v[i][3]= p;
}

//  Creates a vecnodes thanks to the vector<vector<long> > G in argument of the function :
// each columns and each lines are the name of a node and as a consequence G represents the adjacence matrix of the graph
vecnodes vecnodes::creation(vector<vector<long> > G) {
    vecnodes T= vecnodes();
    for (int i(0); i<G.size(); ++i){
        nodes n = nodes(i,-1, infinity,1);
        T.addvecnodes(n);
    }
    return T;
}

// Returns the node n of the vecnodes T
nodes vecnodes::GetNodInVec(int n, vecnodes T) {
    nodes a(T.Getv()[n][0],T.Getv()[n][1],T.Getv()[n][2], T.Getv()[n][3]);
    return a;
}

// Returns the node that has the shortest distance to the initial node among the nodes contained in the vecnodes M.
nodes vecnodes::FindMin(vecnodes  M) {
    long min = infinity;  // initial value of the minimum distance
    nodes* pn;
    nodes j = nodes(0,0,0,0);
    pn= &j;
    vector< vector< long> > T = M.Getv();
    int t = T.size();
    for (int i(0); i < t; i++){
        //If a node as a shorter way than min to the initial node and is in the vecnodes M, than min takes the value of the distance
        //between this node and the initial node
        if (GetNodInVec(i, M).GetDistance() >= 0 && GetNodInVec(i, M).GetDistance()<= min && GetNodInVec(i, M).GetPosition() == 1){
            min = GetNodInVec(i, M).GetDistance();
            nodes n = GetNodInVec(i, M);
            pn = &n;
        }

    }
    // returns the node at the address pn
    return *pn;
}

// if the way between the initial node and b is longer than the way between the initial node and a added to the way between a and b
//then the distance between the initial node and b becomes : the distance between the initial node and a + the distance
// between a and b. Define a as the predecessor of b.
void vecnodes::NewDist(nodes a, nodes b, vector< vector<long> > G, vecnodes* T) {
    int db = b.GetDistance();
    int da = a.GetDistance();
    int na = a.GetName();
    int nb = b.GetName();
    if ( db > da + G[na][nb]){
        (*T).Setv_distance(nb,da + G[na][nb]); // changes directly the distance of the node b in T and not in a copy of T
         b.SetDistance(da + G[na][nb]);
        (*T).Setv_predecessor(nb, na);
         b.SetAnte(na);
    }
}

// Checks if there is again node with position 1 in the vecnodes at the address of the pointer T
bool vecnodes:: NotEmpty(vecnodes* T) {
    for(int i(0); i< (*T).Getv().size(); ++i){
        if (GetNodInVec(i,(*T)).GetPosition() == 1){
            return true;
        };
    }
    return false;
}

// Returns the shortest way between b and a as a vector of int which will be converted as a vector of string
// Containing the names of the metro stations.
// G is the adjacency matrix of the graph G(i,j) = 1 if nodes i and j are directly linked, 0 otherwize.
vector<int> vecnodes::Djikstra(vector< vector<long> > G, nodes b, nodes a) {

    vecnodes T = vecnodes::creation(G); // We creates a vecnodes. Each node has a infinite distance to the initial note.
    //each nodes has a position 1 (is in T) and has no particular predecessor.
    vecnodes *pT = &T;
    T.Setv_distance(b.GetName(), 0); // We give distance 0 to the initial node.
    int k = 0;
    while (NotEmpty(pT) && k < 1000) { // while we have not gone through all the nodes of T we continue to compute the
        // shortest distance between each node and the initial node.
        nodes n = vecnodes::FindMin(T); //Finds the node with the shortest distance to the initial node.
        for (int j(0); j < G.size(); ++j) { //Goes through all the nodes linked with n.
            if (G[n.GetName()][j] != infinity && G[n.GetName()][j] != 0 && GetNodInVec(j, T).GetPosition() == 1) {
                vecnodes::NewDist(GetNodInVec(n.GetName(), T), GetNodInVec(j, T), G,
                                  &T); // Gives teh shortest distance bewteen the node considerate and the initial node
                // and sets n as the predecessor of b in the way.
            }
        }
        T.Setv_position(n.GetName(), 0); // Once we have worked on a node it is removed from T.
        k = k + 1;
        int pct = k*100/353;
        cout << pct << "%" << endl;
    }

    // We enter in A the way between the departure point and the arrival point. To do this we do the way backward by taking
    // all the predecessor of each node and begining by the final node.
    vector<int> A;
    int n_end = a.GetName();
    int n_deb = b.GetName();
    while (n_end != n_deb) {
        A.push_back(n_end);
        n_end = GetNodInVec(n_end, T).GetAnte();
    }
    A.push_back(n_deb);

    std::cout << "le chemin demandé est :" << endl;
/*    for (int i(0); i < A.size(); ++i) {
        std::cout << A[i] << endl;
        std::cout << "<--" << endl;
    }*/

    return A;
}
