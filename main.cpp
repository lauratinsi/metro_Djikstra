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
    vector<vector<long> > M ={{0,1,2,_infinite,_infinite,_infinite,_infinite},{1,0,_infinite,2,_infinite,_infinite,_infinite},
                              {2,_infinite,0,_infinite,4,_infinite,_infinite},{_infinite,2,3,0,2,3,3},
                              {_infinite,_infinite,4,2,0,_infinite,5},{_infinite,3,_infinite,3,_infinite,0,4},
                              {_infinite,_infinite,_infinite,3,5,4,0}};
    std::cout << M.size() << std::endl;


 /*   int* pk;
    int k = 999;
    pk = &k;
    int b = *pk;
    std::cout << b<< std:: endl;*/


    //vecnodes t;
    //t.addvecnodes(nodes1);
    //vector<vector<long> > a=t.Getv();
    //std:: cout << a.size() << std:: endl;
    //std:: cout << a[0][1] << std:: endl;
    //std:: cout << a[0][2] << std:: endl;
    //vecnodes T =vecnodes::creation(M);
    //std::cout << T.Getv().size() << std::endl;
    //std:: cout<< T.Getv().size() << endl;
    //T.Setv_distance(3,46);
    //T.Setv_distance(4, 5);
    //std:: cout<< T.Getv()[3][2] << endl;
    //nodes b = vecnodes::GetNodInVec(3,T);
    //nodes n = vecnodes::FindMin(T);
    //std:: cout<< n.GetName() << endl;
    //std:: cout<< T.Getv()[3][2] << endl;
    //std:: cout << T.Getv()[3][0] << std:: endl;
    //std:: cout << b.GetName() << std:: endl;
    //std:: cout << b.GetAnte() << std:: endl;
    //std:: cout << b.GetDistance() << std:: endl;
    vecnodes K = vecnodes::Djikstra(M, nodes(1,-1,_infinite,1));
    std :: cout << K.Getv().size()<< endl;
    for (int i(0); i< K.Getv().size(); ++i){
        std :: cout << vecnodes::GetNodInVec(i, K).GetName() << endl;
        std :: cout << vecnodes::GetNodInVec(i, K).GetAnte() << endl;
        std :: cout << vecnodes::GetNodInVec(i, K).GetDistance()<< endl;

    }






}
