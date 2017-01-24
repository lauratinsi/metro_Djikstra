//
// Created by Laura TINSI on 23/01/2017.
//
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;


#ifndef METRO1_STATION_H
#define METRO1_STATION_H


class station {
private:
    int num;
    string id;
    string name;
    vector<int> lines;
    vector<string> links;
public:
    station(int, string, string, vector <int>, vector<string>);
    int GetNum();
    string GetId();
    string GetName();
    vector<int> GetLines();
    vector<string> GetLinks();


    void SetNum(int);
    void SetId(string);
    void SetName(string);
    void SetLines(int);
    void Setlinks(string);

    //std::map < vector<int>, vector<string> > const_lines();
    static  vector<string>  ordered(string, int);
    static vector< vector<string> > fullname (string,string, int);
    static vector< vector< vector<string> > > AllPlan(string);
    //static vector<vector<int> > Matrix(vector< vector< vector<string> > >);
    static vector<string> Station(string, string);
    static vector<int> Finder(string , vector< vector<vector<string> > >, vector<string>);
    static vector<vector<long> > MatAdj(vector< vector<vector<string> > >, vector<string>);

};


#endif //METRO1_STATION_H
