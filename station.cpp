//
// Created by Laura TINSI on 25/01/2017.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "station.h"
using namespace std;



station :: station (int i, string d, string n, vector<int> l, vector<string> li){
    num = i;
    id = d;
    name = n;
    lines = l;
    links = li;
}

// Returns the Id_stops of the stations of a metro line in the right order in a vector of string.
// The string argument "address" corresponds to the RATP field containing the Id_stops of each lines in the right
//order. We call this function for each line in the next function called "fullname".
vector<string> station::ordered(string address, int lenth) {

    std :: ifstream field (address); // we open the field and only take the Id_stop among all the informations available
    if (field) {
        vector<string> metroline(lenth);
        string line{};
        int i = 0;
        while (i < lenth+1) {
            int k=0;
            getline(field, line);
            string st(line, 36);
            while (',' != st.at(k)){
                k=k+1;
            }
            string s(st, 0, k);
            if (i>0) {
                metroline[i-1] = s;
            }
            i = i + 1;
        }
        return metroline;
    } else {
        cout << "pbdeux" << endl;
        return {""};
    }
    field.close();
}

// Returns a vector < vector<string> > . Each index i of the vector corresponds to a stop station of the line considered
// for each index the vector< string> contains the real name and the Id_stop of the stop station.
// address1 in argument corresponds to the field containing the real names of the station of the line
// address2 in argument corresponds to the field containing the Id_stops in the right order
vector< vector<string> > station::fullname(string address1, string address2, int lenth) {
    ifstream field(address1);
    vector<string> b = ordered(address2, lenth); // We order the stations of the line
    int sz = b.size();
    vector<vector<string> > T(sz);
    if (field) {
        string ligne{};
        while (getline(field, ligne)) {
            string h(ligne, 0, 10); // We isolate the name of each station in the field
            int l=0;
            while (',' != h.at(l)){
                l=l+1;
            }
            string st(h, 0, l);
            for (int i(0); i < sz; ++i) {
                if (st == b[i]) {
                    string s(ligne, l+2, ligne.size());
                    int j = 0;
                    while (',' != s.at(j)) {
                        j = j + 1;
                    }
                    string name(s, 0, j);
                    T[i] = vector<string>(2);
                    T[i][0] = b[i];
                    T[i][1] = name;

                }
            }
        }

    } else {
        cout << "pb de lecture" << endl;
    }
    field.close();
    return T;
}

// Returns a vector < vector<vector<string> > >. Each index i of the vector corresponds to the real parisian metro line i+1
// for each index i the vector< vector<string>> contains the real name and the Id_stop name of each station of the line i+1
// The address in argument is not the complete address of a field but must be completed as it is done in the function.
// This ables us to call the previous functions for each lines because the fields names are the same except for the
// number of the line.

vector< vector< vector<string> > > station::AllPlan(string address) {
    vector<int> n ={25,25,25,27,22,28,33,38,37,20,13,29,24,9}; // length of each real metro line (from one to 14).
    vector< vector<vector<string> > > M(14);
    for (int i(0); i<14; ++i){ // for each line we call the previous function fullname
        stringstream ss;
        ss << i+1;
        string str = ss.str();
        string address1 = address+str+"/stops.txt";
        string address2 = address+str+"/stop_times.txt";
        int k=n[i];
        M[i]=fullname(address1, address2 ,k);
    }
    return M;
}

// Returns a vector of string with all the Id_stops of all the parisian metro
// The Argument address
vector<string> station::Station(string address, string address2){
    vector<string> S (353);
    int k= 0;
    ifstream field(address);
    if (field) {
        string ligne{};
        while (getline(field, ligne)) {
            string h(ligne, 0, 10);
            int l=0;
            while (',' != h.at(l)){
                l=l+1;
            }
            if(l<10){
                string s(h,0,l);
                vector<vector<vector<string> > > M = AllPlan(address2);
                for (int i(0); i< M.size(); ++i){
                    for(int j(0); j< M[i].size(); ++j){
                        if(s == M[i][j][0]){
                            S[k]=s;
                            k=k+1;
                        }
                    }
                }

            }


        }

    } else {
        cout << "pb de lecture" << endl;
    }

    cout << S.size() << endl;
    field.close();
    return S;
}

// Returns all the positions in S (vector<string> of all the stops Id of the parisian metro) of the neighbours
//of the station whom Id_stop "id" is in argument.
vector<int> station::Finder(string id, vector< vector< vector<string> > > M, vector<string> S){ // trouve tout ses voisins
    vector<int> L(18);
    int k = 0;
    vector<string> Y = SameStation(id,M); // As in the RATP datas stations can have several ID we have to list
    // all the Id available for the same real station.
    for (int s(0); s<Y.size(); ++s){
        string st = Y[s];
        for (int i(0); i<M.size(); ++i){
            for( int j(0); j< M[i].size(); ++j){
                if (st==M[i][j][0]){
                    if (j>0 && j<M[i].size()-1){
                        string ante = M[i][j-1][0];
                        string suiv = M[i][j+1][0];
                        string s = S[0];
                        string st = S[0];
                        int c = 0;
                        int cbis = 0;
                        while (s!= ante && c<355){
                            c = c+1;
                            s = S[c];
                        }
                        while (st!= suiv && cbis<355){
                            cbis = cbis+1;
                            st= S[cbis];
                        }
                        L[k]=c;
                        k=k+1;
                        L[k]= cbis;
                        k=k+1;
                    }
                    if (j==0){
                        string suiv = M[i][j+1][0];
                        string s = S[0];
                        int c = 0;
                        while (s!= suiv && c<355){
                            c = c+1;
                            s = S[c];
                        }
                        L[k]=c;
                        k=k+1;
                    }
                    if (j== M[i].size()-1){
                        string ante = M[i][j-1][0];
                        string s = S[0];
                        int c = 0;
                        while (s!= ante && c<355){
                            c = c+1;
                            s = S[c];
                        }
                        L[k]=c;
                        k=k+1;
                    }
                }
            }
        }
    }
    int nn = 0;
    while (L[nn]!=0){
        nn=nn+1;
    }
    vector<int> l (nn);
    for (int i(0); i<nn; ++i){
        l[i]=L[i];
    }
    return l;
}

// As in the RATP datas stations can have several ID we have to list
// all the Id available for the same real station.
// This function returns a vector of string of all the Id_stop of one real station whom the id argument of
// the function is one of them. M contains all the lines all the name of the stations by lines and their Id_stop.
vector<string> station ::SameStation(string id, vector<vector<vector<string> > > M) {
    vector<string> Y(15);
    Y[0]=id;
    string name;
    int k = 0;
    for(int i(0); i<M.size(); ++i){
        for (int j(0); j<M[i].size(); j++){
            if(M[i][j][0] == id){
                name = M[i][j][1];
            }
        }
    }

    for(int i(0); i<M.size(); ++i){
        for (int j(0); j<M[i].size(); j++){
            if(M[i][j][1] == name){
                name = M[i][j][1];
                Y[k]= M[i][j][0];
                k=k+1;
            }
        }
    }
    return Y;
}

// creates and returns  the Adjacency matrix N of the graph as a vector<vector< long> >
// M in argument is the matrix of all lines, all the stations and all their Id_stops
// S is the list of all the Id_stops of all the stations
// If two stations are linked N(i,j) = 1 otherwize N(i,j) = infinity ( instead of 0 in a classical adjacence matrix )
vector<vector<long> > station::MatAdj(vector<vector<vector<string> > > M, vector<string> S) {
    long infinity = 10000000000000;
    int sz = S.size();
    vector<vector<long> > N (sz);
    for (int i(0); i<sz; ++i){
        vector<int> l = Finder(S[i],M,S);
        N[i] = vector<long>(sz) ;
        for(int j(0); j<sz; ++j){
            N[i][j] = infinity;
            for(int k(0); k<l.size(); ++k){
                if(j==l[k]){
                    N[i][j]= 1;
                }
            }
        }

    }
    return N;
}

// Way permits to traduct  the vector<int> A in arguments which is the output of vecnodes::Djikstra into the real
// station name. It returns in the order the station names of the optimal way between two stations.
// W is the matrix of all the line, all the stations names and all their Id_stops.
vector<string> station::Way(vector<int> A, vector<vector<vector<string> > > W, vector<string> S) {
    int a = A.size();
    int c = 0;
    vector<string> way(a);
    for (int k (0); k<a; ++k){
        for(int i(0); i<W.size(); ++i){
            for(int j(0); j<W[i].size(); ++j){
                if(W[i][j][0] == S[A[k]]){
                    way[c]=W[i][j][1];
                    c = c+1;
                }
            }

        }
    }
    for(int i(0); i<a; ++i){
        cout << way[i] << endl;
    }
    return way;

}

// This is in this function that the user will enter the names of the stations between which he wants to travel.
// This function will return their position in the list of all the station S and will permit to apply the djikstra.
// W is again the matrix of all the line, all the stations names and all their Id_stops.
vector<int> station::enter(string dep,string arr,vector< vector<vector<string> > > W, vector<string> S) {
    vector<int> A (2);
    for(int i(0); i<W.size(); ++i){
        for(int j(0); j<W[i].size(); ++j){
            string s =W[i][j][1];
            string st(s,1, W[i][j][1].size()-2);

            if(dep == st){
                int k = 0;
                cout << "ici" << endl;
                while(W[i][j][0] != S[k]){
                    k=k+1;
                }
                A[0]=k;
            }
            if(arr == st){
                int b = 0;
                while(W[i][j][0] != S[b]){
                    b=b+1;
                }
                A[1]=b;
            }
        }
    }
    return A;
}

vector<vector<string> > station::design(vector<string> way, vector<vector<vector<string> > > W) {
    vector<vector<string>> Y(way.size());
    string id;
    for(int k(0); k<way.size(); ++k){
        Y[k]=vector<string>(15);
        for (int i(0); i<W.size(); ++i){
            for(int j(0); j<W[i].size(); ++j){
                if(way[k]==W[i][j][1]){
                    id = W[i][j][0];
                    Y[k]=SameStation(id, W);
                }
            }
        }


    }
    return Y;
}
