#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

int main() {
    ifstream field("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_6/stops.txt");
    list<string> li;
    if (field) {
        string ligne{};
        while (getline(field, ligne)) {
            cout << ligne << endl;
            string st(ligne, 0, 4);
            string a = st + ",";
            li.push_back(a);
        }

        cout << "ok" << endl;
    } else {
        cout << "pb de lecture" << endl;
    }
    field.close();
    ifstream fi("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_LINES/RATP_GTFS_METRO_6/stop_times.txt");
    string l{};
    if (fi) {
        string line{};
        int i = 0;
        while (i < 29) {
            getline(fi, line);
            cout << line << endl;
            i = i + 1;
            string st(line, 36, 36);
            l.append(st);
        }

        cout << "okkkk" << endl;
    } else {
        cout << "pbdeux" << endl;
    }
    cout << l << endl;
    fi.close();
    ifstream full("/Users/lauratinsi/Desktop/ENSAE/2A/C++/RATP_GTFS_FULL/stops.txt");
    if (full){
        string l{};
        list<string> a {};
        getline (full,l, char (','));
        cout<< l << endl;
        }

    }

