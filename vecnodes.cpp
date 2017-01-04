//
// Created by Laura TINSI on 29/12/2016.
//
#include <iostream>
#include "nodes.h"
#include <list>
#include <vector>
#include "vecnodes.h"
long infinity= 10000000;
using namespace std;



void vecnodes::addvecnodes(nodes n) {
    v.push_back({n.GetName(),n.GetAnte(),n.GetDistance(),n.GetPosition()});
}


vector< vector<long>> vecnodes::Getv(){
    return v;
}

void vecnodes::Setv_predecessor(int i, int p){
    v[i][1]= p;
}

void vecnodes::Setv_distance(int i, int d){
    v[i][2]= d;
}

void vecnodes::Setv_position(int i, int p) {
    v[i][3]= p;
}

vecnodes vecnodes::creation(vector<vector<long> > G) {
    vecnodes T= vecnodes();
    for (int i(0); i<G.size(); ++i){
        nodes n = nodes(i,-1, infinity,1);
        T.addvecnodes(n);
    }
    return T;
}
nodes vecnodes::GetNodInVec(int n, vecnodes T) {
    nodes a(T.Getv()[n][0],T.Getv()[n][1],T.Getv()[n][2], T.Getv()[n][3]);
    return a;
}

nodes vecnodes::FindMin(vecnodes  M) {
    long min = infinity;
    nodes* pn;
    nodes j = nodes(0,0,0,0);
    pn= &j;
    vector< vector< long> > T = M.Getv();
    for (int i(0); i < T.size(); i++){
        if (GetNodInVec(i, M).GetDistance() >= 0 && GetNodInVec(i, M).GetDistance()< min && GetNodInVec(i, M).GetPosition() == 1){ // pas normal qu'on doive mettre min-1 au lieu de min
            min = GetNodInVec(i, M).GetDistance();
            //std:: cout<< "le min choisi est"<< std::endl;
            //std:: cout<< min << std::endl;
            nodes n = GetNodInVec(i, M);
            //std:: cout<< "le noeud choisi est"<< std::endl;
            //std:: cout<< n.GetName() << std::endl;
            pn = &n;
        }

    }
    return *pn;
}


void vecnodes::NewDist(nodes a, nodes b, vector< vector<long> > G, vecnodes* T) {
    int db = b.GetDistance();
    int da = a.GetDistance();
    int na = a.GetName();
    int nb = b.GetName();
    if ( db > da + G[na][nb]){
        (*T).Setv_distance(nb,da + G[na][nb]);
         b.SetDistance(da + G[na][nb]);
        (*T).Setv_predecessor(nb, na);
         b.SetAnte(na);
    }
}

bool vecnodes:: NotEmpty(vecnodes* T) {
    for(int i(0); i< (*T).Getv().size(); ++i){
        if (GetNodInVec(i,(*T)).GetPosition() == 1){
            return true;
        };
    }
    return false;
}

vecnodes vecnodes::Djikstra(vector< vector<long> > G, nodes b, nodes a){

    vecnodes T = vecnodes:: creation(G);
    vecnodes* pT = &T;
    //std ::cout << "taille dans le djikstra\n" << std:: endl;
    //std ::cout << T.Getv().size() << std:: endl;
    T.Setv_distance(b.GetName(),0); // On donne le coût 0 au noeud de départ.
   /* for (int i(0); i< T.Getv().size(); ++i){
        std :: cout << vecnodes::GetNodInVec(i, T).GetName() << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetAnte() << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetDistance()<< endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetPosition()<< endl;
        std :: cout << "\n" << endl;

    }
    std ::cout << "fin de T\n" << std:: endl;*/
    int k = 0;
    while(NotEmpty(pT) && k<180){ // Attention il faudra trouver un autre système d'arret
        nodes n = vecnodes::FindMin(T);
        //std ::cout << "le nom du noeud en cours est" << std:: endl;
        //std ::cout << n.GetName() << std:: endl;
        //std ::cout << "\n" << std:: endl;
        for (int j(0);j<G.size();++j){
            if (G[n.GetName()][j] != infinity && G[n.GetName()][j] !=0 && GetNodInVec(j,T).GetPosition()==1){

                vecnodes::NewDist(GetNodInVec(n.GetName(),T),GetNodInVec(j,T),G, &T); // la mettre dans le bon truc pour changer le set_pedessesor

            }

        }
        //std ::cout << "le predecesseur de n est mnt :" << std:: endl;
        //std ::cout << GetNodInVec(n.GetName(),T).GetAnte() << std:: endl;
        //std ::cout << "la distance de F est   :" << std:: endl;
        //std ::cout << GetNodInVec(5,T).GetDistance() << std:: endl;
        T.Setv_position(n.GetName(),0);
        //std ::cout << "position du noeud qu'on enlève" << std:: endl;
        //std ::cout << GetNodInVec(n.GetName(),T).GetPosition() << std:: endl;
        k= k+1;
    }
/*    std :: cout << "FINAL" << endl;
    for (int i(0); i< T.Getv().size(); ++i){
        std :: cout << "nom du noeud" << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetName() << endl;
        std :: cout << "nom du predecesseur" << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetAnte() << endl;
        std :: cout << "distance à la source" << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetDistance()<< endl;
        std :: cout << "Position" << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetPosition()<< endl;
        std :: cout << "\n" << endl;

    }*/
    vector<int> A;
    int n_end = a.GetName();
    int n_deb = b.GetName();
    while(n_end!=n_deb){
        A.push_back(n_end);
        n_end = GetNodInVec(n_end,T).GetAnte();
    }
    A.push_back(n_deb);
    std :: cout << "le chemin demandé est :"<< endl;
    for(int i(0);i <A.size();++i){
        std :: cout << A[i]<< endl;
        std :: cout << "<--"<< endl;
    }

    return T;

}