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
    std::cout << "Hello, World!" << std::endl;
    //nodes nodes1(1,5,3);
    //nodes1.SetAnte(6);
    //std:: cout << nodes1.GetAnte() << std::endl;
    vector<vector<long> > M ={{0,1,2,_infinite,_infinite,_infinite,_infinite},{1,0,_infinite,2,_infinite,3,_infinite},
                              {2,_infinite,0,_infinite,4,_infinite,_infinite},{_infinite,2,3,0,2,3,3},
                              {_infinite,_infinite,4,2,0,_infinite,5},{_infinite,3,_infinite,3,_infinite,0,4},
                              {_infinite,_infinite,_infinite,3,5,4,0}};
    std::cout << M.size() << std::endl;


    vector<int> K =vecnodes::Djikstra(M, nodes(1,-1,_infinite,1), nodes(2,-1,_infinite,1));


    // PARTIE CREATION DE MATRICE

    //vector<string> t = station::ordered("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_6/stop_times.txt",28);
    //station::fullname("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_1/stops.txt","/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_1/stop_times.txt", 25);
    vector<vector<vector<string> > > W = station::AllPlan("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_");
    vector<string> S =station::Station("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_FULL/stops.txt" ,"/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_");
    vector<string> A = station::SameStation("1824",W);
    vector<int>  L = station::Finder("1166834",W,S);
    vector<vector<long> > N = station::MatAdj(W,S);
    //cout<< S[5] << endl;
    //cout << S[4] << endl;
    //cout << N[1][8] << endl;
    //for(int(i); i<N.size(); ++i){
    //    cout << N[5][i] << endl;
    //}
/*    cout<< S[6] << endl;
    cout<< S[74] << endl;
    cout<< S[49] << endl;
    cout<< S[154] << endl;
    cout<< S[71] << endl;
    cout<< S[123] << endl;
    cout<< S[283] << endl;
    cout<< S[309] << endl;*/


    //JE comprends pas pk ca marche pas ca
    //vector<int> B = station::enter("Dupleix", "Oberkampf", W,S);
    //cout<< B[0] << endl;
    //cout<< B[1] << endl;
    //vector<int> F = vecnodes::Djikstra(N, nodes(6,-1,_infinite,1), nodes(309,-1,_infinite,1));
    //vector<int> F = vecnodes::Djikstra(N, nodes(18,-1,_infinite,1), nodes(39,-1,_infinite,1));
    //vector<int> F = vecnodes::Djikstra(N, nodes(180,-1,_infinite,1), nodes(67,-1,_infinite,1));
    vector<int> F = vecnodes::Djikstra(N, nodes(56,-1,_infinite,1), nodes(207,-1,_infinite,1));
    station::Way(F, W, S);



}
