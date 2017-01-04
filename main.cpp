#include <iostream>
#include "nodes.h"
#include "vecnodes.h"
#include <list>
#include <vector>
long _infinite = 10000000000000000;
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    //nodes nodes1(1,5,3);
    //nodes1.SetAnte(6);
    //std:: cout << nodes1.GetAnte() << std::endl;
    vector<vector<long> > M ={{0,1,2,_infinite,_infinite,_infinite,_infinite},{1,0,_infinite,2,_infinite,3,_infinite},
                              {2,_infinite,0,_infinite,4,_infinite,_infinite},{_infinite,2,3,0,2,3,3},
                              {_infinite,_infinite,4,2,0,_infinite,5},{_infinite,3,_infinite,3,_infinite,0,4},
                              {_infinite,_infinite,_infinite,3,5,4,0}};
    std::cout << M.size() << std::endl;


    vecnodes K =vecnodes::Djikstra(M, nodes(1,-1,_infinite,1), nodes(2,-1,_infinite,1));



}
