//
// Created by Laura TINSI on 23/01/2017.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
//#include <altivec.h>
#include "station.h"
using namespace std;

station :: station (int i, string d, string n, vector<int> l, vector<string> li){
    num = i;
    id = d;
    name = n;
    lines = l;
    links = li;
}

string station::GetName() {
    return name;
}

int station::GetNum() {
    return num;
}

string station::GetId() {
    return id;
}

vector<string> station::GetLinks() {
    return links;
}

void station::SetName(string a) {
    name = a;
}
void station::SetId(string b) {
    id = b;
}
void station::SetNum(int c) {
    num = c;
}

void station::SetLines(int a) {
    int i = lines.size();
    lines[i]=a;
}

void station::Setlinks(string s) {
    int i = links.size();
    links[i]=s;
}

/*std::map < vector<int>, vector<string> > station::const_lines() {

}*/

vector<string> station::ordered(string address, int lenth) {
    //std :: ifstream field ("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_6/stop_times.txt");
    /*stringstream ss;
    ss << number;
    string str = ss.str();
    static string address1 = address+str+"/stop_times.txt";
    //cout << address1 << endl;*/
    std :: ifstream field (address);
    if (field) {
        vector<string> metroline(lenth);
        string line{};
        int i = 0;
        while (i < lenth+1) {
            int k=0;
            getline(field, line);
            //cout << line << endl;
            string st(line, 36);
            //cout << st << endl;
            while (',' != st.at(k)){
                k=k+1;
            }
            string s(st, 0, k);
      //      cout << s << endl;
            //string temp;
            if (i>0) {
                metroline[i-1] = s;

            }//metroline[i-1][1] = s;
        //    cout << "je suis ici" << endl;
            i = i + 1;
        }
        //cout << "je suis ici" << endl;
//        for (int i(0); i<metroline.size(); ++i){
//            cout<< metroline[i] <<endl;
//        }
        //cout << "okkkk" << endl;
        return metroline;

    } else {
        cout << "pbdeux" << endl;
        return {""};
    }
    //cout << l << endl;

    field.close();

}
vector< vector<string> > station::fullname(string address1, string address2, int lenth) {
/*    stringstream ss;
    ss << a;
    string str = ss.str();
    static string address1 = address+str+"/stops.txt";
    static string address2 = address+str+"/stop_times.txt";*/
    //cout << address1 << endl;
    //cout << address2 << endl;
    ifstream field(address1);
    vector<string> b = ordered(address2, lenth);
    int sz = b.size();
    //cout<< sz << endl;
    vector<vector<string> > T(sz);

    if (field) {
        string ligne{};
        while (getline(field, ligne)) {
            string h(ligne, 0, 10);
            int l=0;
            while (',' != h.at(l)){
                l=l+1;
            }
            string st(h, 0, l);
      //      cout << st << endl;
            for (int i(0); i < sz; ++i) {
                if (st == b[i]) {
                    string s(ligne, l+2, ligne.size());
                    int j = 0;
                    while (',' != s.at(j)) {
                        j = j + 1;
                    }
                    string name(s, 0, j);
        //            cout << name << endl;
                    T[i] = vector<string>(2);
                    T[i][0] = b[i];
                    T[i][1] = name;

                }
            }
        }
       // cout << "ok" << endl;
        /*for (int l(0); l<T.size(); ++l){
            cout<< T[l][0] << endl;
            cout<< T[l][1] << endl;
        }*/
    } else {
        cout << "pb de lecture" << endl;
    }
    field.close();
    return T;
}


vector< vector< vector<string> > > station::AllPlan(string address) {
    vector<int> n ={25,25,25,27,22,28,33,38,37,20,13,29,24,9};
    //vector<vector<string> > t = fullname(address, 1 ,25);
    vector< vector<vector<string> > > M(14);
    for (int i(0); i<14; ++i){
        stringstream ss;
        ss << i+1;
        string str = ss.str();
        string address1 = address+str+"/stops.txt";
        string address2 = address+str+"/stop_times.txt";
        int k=n[i];
        //cout << address1 << endl;
        //cout << address2 << endl;
        //cout<< i << endl;
        //cout<<n[i]<< endl;
        M[i]=fullname(address1, address2 ,k);
    }
    return M;
}

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
                //cout<< "je suis la " << endl;
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
    //for(int i(0); i< S.size(); ++i){
    //    cout << S[i] << endl;
    //}
    cout << S.size() << endl;
    field.close();
    return S;
}

vector<int> station::Finder(string id, vector< vector< vector<string> > > M, vector<string> S){
    vector<int> L(10);
    int k = 0;
    cout<< id << endl;
/*    for (int i(0); i< M[5].size(); ++i){
        cout << M[5][i][0]<< endl;
    }*/
    for (int i(0); i<M.size(); ++i){

        for( int j(0); j< M[i].size(); ++j){

            if (id==M[i][j][0]){
                //cout<< "je suis la " << endl;
                if (j>0 && j<M[i].size()-1){
                    //cout<< "je suis la2 " << endl;
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
                    //cout<< s << endl;
                    //cout<< st << endl;
                    L[k]=c;
                    //cout<< L[k]<< endl;
                    k=k+1;
                    L[k]= cbis;
                    //cout<< L[k]<< endl;
                    k=k+1;
                }
                if (j==0){
                    //cout << "suis la " << endl;
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
                    //cout<< "suis la2"<< endl;
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

    //cout<< S[29] << endl;
    //cout<< S[34] << endl;
    int nn = 0;
    while (L[nn]!=0){
        nn=nn+1;
    }
    vector<int> l (nn);
    for (int i(0); i<nn; ++i){
        l[i]=L[i];
    }
/*    for(int i(0); i< l.size();++i){
        cout<< l[i]<< endl;
        cout<< S[l[i]]<< endl;
    }*/
    return l;
}

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
/*vector< vector<int> > station::Matrix(vector< vector<vector<string> > > M){
    vector<string> S(400)  ;
    int l=0;
    for(int i(0); M.size() > i; ++i){
        for(int j(0); j<M[i].size(); ++j){
            string id = M[i][j][0];
            string name = M[i][j][0];
            S[l]=id;
            for(int k(i+1); k<M.size(); ++k){
                *//*if(std::find(M[k].begin(), M[k].end(), {id, name} )!=M[k].end())
                {
                    for (int s(0); s<M[k].size(); ++s){

                    }
                }*//*

            }


            *//*bool a = true;
            while(S[l]!= ""){
                if (S[l].GetId==M[i][j][0]){
                    S[l].SetLines(i+1);
                    a = false;
                }
                l=l+1;
            }
            if (a==false){
                S[l].SetName(M[i][j][1]);
                S[l].SetLines(i+1);
                S[l].SetId(M[i][j][0]);
                S[l].SetNum(l);
                if (j>0){
                    S[l].Setlinks(M[i][j-1][0]);
                }
                if(j<M[i].size()-1){
                    S[l].Setlinks(M[i][j+1][0]);
                }


            }*//*

        }
    }
}*/
