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
    /*if (v.size()< n+1){
        break;//return std::cout << "this nodes is not in vecnodes" << endl;
    }*/
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
            std:: cout<< "le min choisi est"<< std::endl;
            std:: cout<< min << std::endl;
            nodes n = GetNodInVec(i, M);
            std:: cout<< "le noeud choisi est"<< std::endl;
            std:: cout<< n.GetName() << std::endl;
            pn = &n;
        }

    }
    return *pn;
}
/*
nodes vecnodes::FindMin(vecnodes  M) {
    long min = infinity;
    nodes* pn;
    nodes j = nodes(0,0,0,1);
    pn= &j;
    vector< vector< long> > T = M.Getv();
    for (int i(0); i < T.size(); i++){
        if (0<=GetNodInVec(i, M).GetDistance() < min-1) { // pas normal qu'on doive mettre min-1 au lieu de min
            //&& GetNodInVec(i, M).GetPosition() == 1)
            min = GetNodInVec(i, M).GetDistance();
            nodes n = GetNodInVec(i, M);
            std:: cout<< "le noeud choisi est"<< std::endl;
            std:: cout<< i << std::endl;
            pn = &n;
        }

    }
    return *pn;
}
*/

/*void vecnodes::delete_in_vec(int i){
    vector<long> temp = v[0];
    v[0]= v[i];
    v[i]=temp;
    v.erase(v.begin());

}*/

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


vecnodes vecnodes::Djikstra(vector< vector<long> > G, nodes b){
    // Attention la il faudra prendre le vecnodes en reference et pas en valeur pour pas qu'il y ait de copies qd utilisation de fonction
    vecnodes T = vecnodes:: creation(G);
    vecnodes* pT = &T;
    std ::cout << "taille dans le djikstra\n" << std:: endl;
    std ::cout << T.Getv().size() << std:: endl;
    T.Setv_distance(b.GetName(),2); // On donne le coût 0 au noeud de départ.
    for (int i(0); i< T.Getv().size(); ++i){
        std :: cout << vecnodes::GetNodInVec(i, T).GetName() << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetAnte() << endl;
        std :: cout << vecnodes::GetNodInVec(i, T).GetDistance()<< endl;
        std :: cout << "\n" << endl;

    }
    std ::cout << "fin de T\n" << std:: endl;
    int k = 0;
    while(NotEmpty(pT) && k<180){ // Attention il faudra trouver un autre système d'arret
        nodes n = vecnodes::FindMin(T);
        std ::cout << "le nom du noeud en cours est" << std:: endl;
        std ::cout << n.GetName() << std:: endl;
        std ::cout << "\n" << std:: endl;
        for (int j(0);j<G.size();++j){
            if (G[n.GetName()][j] != infinity && G[n.GetName()][j] !=0 && GetNodInVec(j,T).GetPosition()==1){

                vecnodes::NewDist(GetNodInVec(n.GetName(),T),GetNodInVec(j,T),G, &T); // la mettre dans le bon truc pour changer le set_pedessesor
            }
        }
        T.Setv_position(n.GetName(),0);
        std ::cout << n.GetPosition() << std:: endl;
        k= k+1;
    }
    return T;
    // le pb est que comme on n'enlève pas à chaque fois l'élément de la liste, on y repasse à chaque fois (dérouler
    // pour A, puis B => B reste dans la liste et est recouté dans la boucle for alors qu'il ne faudrait pas ?
    //
}