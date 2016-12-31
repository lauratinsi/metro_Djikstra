//
// Created by Laura TINSI on 26/12/2016.
//

#include "nodes.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

long _infinity = 10000000000000000;
//int const _size = 60;
nodes::nodes(int a, int b, long c){
    name=a;
    predecessor=b;
    distance=c;
}

// Accessors
long nodes::GetDistance() {
    return distance;
}
int nodes::GetName() {
    return name;
}
int nodes::GetAnte() {
    return predecessor;
}

//Setters
void nodes::SetName(int i) {
    name = i;
}
void nodes::SetDistance(long d) {
    distance = d;
}
void nodes::SetAnte(int n) {
    predecessor = n;
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









