//
// Created by HP on 03-Jun-22.
//
#include <iostream>
#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdlib>

#ifndef PRACTICECPP_FUNCTIONS_CLASSES_H
#define PRACTICECPP_FUNCTIONS_CLASSES_H
#endif //PRACTICECPP_FUNCTIONS_CLASSES_H

using namespace std;


class City;
class Transport;
class Connection;
class Coordinate;
class Node;

City *getCityAddress(const string& basicString, City *city, int cityNum);
void getInfoFromLine(ifstream& file, Connection *connection, City *city, int cityNum);
void getNameNCoordinateFromLine(ifstream& file, City *city);
double getDistance(City* a, City* b);
bool isInClosedList(const string& basicString, const vector<Node*>& closed);
Node* isInOpenList(const string& basicString, vector<Node*>& open);




class Coordinate{
public:
    float x, y;
    explicit Coordinate(float x=0, float y=0){
        this->x=x;
        this->y=y;
    }
};
class Transport{
public:
    float cost;
    float time;
    Transport(float t, float c){
        cost = c;
        time = t;
    }
};
class Connection{
public:
    City* link;
    Transport bus, plane, train;
    explicit Connection(City* link= nullptr, float btime=0, float bcost=0, float ttime=0, float tcost=0, float ptime=0, float pcost=0)
            : bus(btime, bcost), train(ttime, tcost), plane(ptime, pcost)
    {
        this->link = link;
    }
};
class City{
public:
    string name;
    vector<Connection> connection;
    Coordinate loc;
    explicit City(string n=""){
        name=std::move(n);
        loc.x=0, loc.y=0;
    }
};
class Node{
public:
    double g_prevDist;
    double f;
    double h_distFromDestination;
    City* nodeCity;
    string path;
    Node(double g_prvDst, City* nodeCity, const string& p, City* destination)
    {
        this->nodeCity=nodeCity;
        g_prevDist=g_prvDst;
        h_distFromDestination= getDistance(nodeCity, destination);
        f=g_prevDist+h_distFromDestination;
        path+=p;
    }
};

Node* isInOpenList(const string& basicString, vector<Node*>& open) {
    for (auto & i : open) {
        if (i->nodeCity->name==basicString ){
            return reinterpret_cast<Node *>(&i);
        }
    }
    return nullptr;
}
struct sort_pred {
    bool operator()(const Node* left, const Node* right) {
        return left->f > right->f;
    }
};
City *getCityAddress(const string& basicString, City *city, int cityNum)
{
    for (int i = 0; i < cityNum; ++i) {
        if (basicString==city[i].name){
            return city;
        }
    }
    cout<<"city not found\nMay behave weirdly\n";
    return nullptr;
}
bool isInClosedList(const string& basicString, const vector<Node *>& closed) {
    for (auto & i : closed) {
        if (i->nodeCity->name==basicString ){
            return true;
        }
    }
    return false;
}
double getDistance(City* a, City* b){
    return sqrt(pow(a->loc.x - b->loc.x, 2) + pow(a->loc.y - b->loc.y, 2));
}
void getInfoFromLine(ifstream& file, Connection *connection, City *city, int cityNum){
    string s, info[8];
    getline(file, s);
    int i=0, j=0; size_t n=s.size();
    while (i<n)//until line has ended
    {
        while(s[i]!=',' && i<n) //take each word
        {
            info[j]+= s[i]; //cout<<s[i];//debug line-------
            i++;
        }//cout<<", ";
        i++;
        j++;
    }//cout<<"\n";
    connection->link= getCityAddress(info[0], city, cityNum);
    connection->bus.time =  (float)atof(info[1].c_str());
    connection->bus.cost =  (float)atof(info[2].c_str());
    connection->train.time= (float)atof(info[3].c_str());
    connection->train.cost= (float)atof(info[4].c_str());
    connection->plane.time= (float)atof(info[5].c_str());
    connection->plane.cost= (float)atof(info[6].c_str());
}
void getNameNCoordinateFromLine(ifstream& file, City *city) {
    string s, info[8];
    getline(file, s);
    int i = 0, j = 0;

    while (s[i] != '\n' && s[i]!='\0')//until line has ended
    {
        while (s[i] != ',' && s[i] != '\n' && s[i]!='\0') //take each word
        {
            info[j] += s[i];
            i++;
        }
        i++;
        j++;
    }
    city->name = info[0];
    city->loc.x= atof(info[1].c_str());
    city->loc.y= atof(info[2].c_str());
}