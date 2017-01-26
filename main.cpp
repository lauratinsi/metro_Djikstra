#include <iostream>
#include "nodes.h"
#include "vecnodes.h"
#include <list>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include "station.h"

long _infinite = 10000000000000;
using namespace std;
int main() {


 /*   vector<vector<long> > M ={{0,1,2,_infinite,_infinite,_infinite,_infinite},{1,0,_infinite,2,_infinite,3,_infinite},
                              {2,_infinite,0,_infinite,4,_infinite,_infinite},{_infinite,2,3,0,2,3,3},
                              {_infinite,_infinite,4,2,0,_infinite,5},{_infinite,3,_infinite,3,_infinite,0,4},
                              {_infinite,_infinite,_infinite,3,5,4,0}};
    std::cout << M.size() << std::endl;


    vector<int> K =vecnodes::Djikstra(M, nodes(1,-1,_infinite,1), nodes(2,-1,_infinite,1));*/


    // Construction of the Adjacency matrix

    vector<vector<vector<string> > > W = station::AllPlan("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_");
    vector<string> S =station::Station("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_FULL/stops.txt" ,"/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_");
    vector<vector<long> > N = station::MatAdj(W,S);





    vector<int> B = station::enter("Dupleix" ,"Oberkampf", W,S);
    cout<< B[0] << endl;
    cout<< B[1] << endl;
    //cout << S[208] << endl;
    //cout << S[157] << endl;
    //vector<int> F = vecnodes::Djikstra(N, nodes(6,-1,_infinite,1), nodes(309,-1,_infinite,1));
    //vector<int> F = vecnodes::Djikstra(N, nodes(18,-1,_infinite,1), nodes(39,-1,_infinite,1));
    //vector<int> F = vecnodes::Djikstra(N, nodes(180,-1,_infinite,1), nodes(67,-1,_infinite,1));
    //vector<int> F = vecnodes::Djikstra(N, nodes(56,-1,_infinite,1), nodes(207,-1,_infinite,1));
    vector<int> F = vecnodes::Djikstra(N, nodes(B[0],-1,_infinite,1), nodes(B[1],-1,_infinite,1));
    vector<string> A = station::Way(F, W, S);

    //Affichage

    vector<vector<string>> D = station::design(A, W);
    for(int i(0); i<D.size(); ++i){
        cout<< D[2][i] << endl;
    }



}
