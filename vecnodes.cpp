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
        //cout << min << endl;
        //cout << "est ce qu'on devrait rentrer dans la boucle" << endl;
        //cout << GetNodInVec(i, M).GetDistance() << endl;
        if (GetNodInVec(i, M).GetDistance() >= 0 && GetNodInVec(i, M).GetDistance()<= min && GetNodInVec(i, M).GetPosition() == 1){ // pas normal qu'on doive mettre min-1 au lieu de min
            //cout << "kikou"<< endl;
            min = GetNodInVec(i, M).GetDistance();
            nodes n = GetNodInVec(i, M);
            pn = &n;
        }

    }
    // Je pense qu'il faut faire une condition ici au cas ou on ne fait rien : on ne rentre pas dans le if il faut qu'il renvoie autre chose que le

    // comprendre pourquoi il ne rentre âs dans la boucle à partir de 5 .
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

vector<int> vecnodes::Djikstra(vector< vector<long> > G, nodes b, nodes a) {

    vecnodes T = vecnodes::creation(G);
    cout << "lalalallaalla" << endl;
    vecnodes *pT = &T;
    T.Setv_distance(b.GetName(), 0); // On donne le coût 0 au noeud de départ.
    int k = 0;
    while (NotEmpty(pT) && k < 1000) { // Attention il faudra trouver un autre système d'arret
        nodes n = vecnodes::FindMin(T);// PAS normale qu'il trouve 0 alors qu'il es t censé plus y etre.
        //cout << "noeud en cours" << endl;
        //cout << n.GetName() << endl;
        //FAIRE UN TRUC DANS LE CAS OU LES DEUX STATION SONT DIRECTMENT RELI2ES QUI SOIT PLUS COURT
        for (int j(0); j < G.size(); ++j) {
            //cout<< "avant et position du noeud " << endl;
            //cout<< j << endl;
            //cout << GetNodInVec(j, T).GetPosition()<< endl;
            if (G[n.GetName()][j] != infinity && G[n.GetName()][j] != 0 && GetNodInVec(j, T).GetPosition() == 1) {
                vecnodes::NewDist(GetNodInVec(n.GetName(), T), GetNodInVec(j, T), G,
                                  &T); // la mettre dans le bon truc pour changer le set_pedessesor
                //cout<< "ici" << endl;
                //cout<< j << endl;
                //cout << "la distance est maintenant" << endl;
                //cout<< GetNodInVec(j,T).GetDistance()<< endl;

            }
        }
        T.Setv_position(n.GetName(), 0);
        k = k + 1;
        //cout<< "nombre de tour" << endl;
        cout << k << endl;
        //cout << "ok" << endl;
    }

    vector<int> A;
    int n_end = a.GetName();
    int n_deb = b.GetName();
    while (n_end != n_deb) {
        A.push_back(n_end);
        n_end = GetNodInVec(n_end, T).GetAnte();
    }
    A.push_back(n_deb);
    std::cout << "le chemin demandé est :" << endl;
    for (int i(0); i < A.size(); ++i) {
        std::cout << A[i] << endl;
        std::cout << "<--" << endl;
    }

    return A;
}
