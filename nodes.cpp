//
// Created by Laura TINSI on 26/12/2016.
//

#include "nodes.h"
#include <iostream>
#include <list>
using namespace std;

long _infinity = 10000000000000000;
int const _size = 60;

// Accessors
int nodes::GetDistance() {
    return distance;
}
int nodes::GetName() {
    return name;
}
std::list<int> nodes::Getpath() {
    return path;
}

//Setters
void nodes::SetName(int i) {
    name = i;
}
void nodes::SetDistance(int d) {
    distance = d;
}
void nodes::SetPath(nodes n) {
    path.push_back(n.name);
}

//Others functions

bool nodes::equals(nodes a, nodes b) {
    if (a.name == b.name){
        return true;
    }
    else {
        return false;
    }
}

void nodes::NewDist(nodes a, nodes b, vector< vector<int> > G) {
    int db = b.GetDistance();
    int da = a.GetDistance();
    int na = a.GetName();
    int nb = b.GetName();
    if ( db > da + G[na][nb]){
        b.SetDistance(da + G[na][nb]);
        b.SetPath(a);
    }
}



