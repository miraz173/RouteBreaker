
#include "functions&Classes.h"

using namespace std;




int main(){
    /*---------------variables declaration---------------------*/
    int cityNumber, connectionSize;
    string line, temp, a="E:\\Codes\\CPP\\practiceCPP\\city.txt";
    /*----------------variables declared----------------------*/

    /*-------------------open text file-----------------------*/
    ifstream file(a.c_str());
    if (!file){
        cout<<"info.text not found\n";
        system("pause");
        return -1;
    }
    else{
        cout<<"Text file opened successfully\n";
    }
    /*------------------text file opened----------------------*/

    /*----------------get number of cities---------------------*/
    getline(file, line);
    cityNumber= atoi(line.c_str());
    /*----------------get number of cities---------------------*/

    City city[cityNumber];  //City objects are declared

    /*----------------get name and coordinate of cities----------------------*/
    for (int i = 0; i < cityNumber; ++i) {
        getNameNCoordinateFromLine(file, city+i);
        cout<<city[i].name<<" "<<city[i].loc.x<<" "<<city[i].loc.y<<"\n";
    }
    /*----------------got name and coordinate of cities---------------------*/

    /*-------------discard the 3 lines with comments-----------*/
    getline(file, line);
    getline(file, line);
    getline(file, line);
    /*------------discarded the 3 lines with comments----------*/

    /*------------take information of edges of the node------------*/
    for (int i = 0; (i < cityNumber)&& file; ++i) {
        getline(file, line);    //line with spaces
        getline(file, line);    // discard the line with comments
        if(!getline(file, line))//get city name
        {
            cout<<"getline() 3 failed\n";
            return -3;
        }
        if (city[i].name == line) {    //check if city name is same as the object name
            line.clear();
            if(!getline(file, line))
            {
                cerr<<"getline() 4 failed\n";
            }//take edge number
            connectionSize= atoi(line.c_str()); //assign number of edges of the node

            for (int j = 0; j < connectionSize; ++j) {
                Connection tempConnection;
                city[i].connection.push_back(tempConnection);
                getInfoFromLine(file, &city[i].connection[j], city, cityNumber);
            }
        }
        else
        {
            cerr << "city infos are not defined in order of initial declaration\n";
            return -1;
        }
    }
    /*------------took information of edges of the node------------*/

    /*------------------UI----------------*/
    system("cls");
    int origin, destination;
    cout<<"Available cities: ";
    for (int i = 0; i < cityNumber; ++i) {
        cout<<i<<") "<<city[i].name<<", ";
    }
    cout<<"\nEnter Origin City Number: ";
    cin>>origin;
    cout<<"Enter Destination City Number: ";
    cin>>destination;
    /*------------------UI----------------*/


    /*-----------------A* algorithm-----------------*/
    City* originCity  =city+origin;
    City* destinationCity =city+destination;
    vector<Node*> openList, closed;
    Node* current, *tempNode, *location;

    current=new Node(0, originCity, "", destinationCity);

    while (current->nodeCity->name != destinationCity->name)
    {
        for (int i = 0; i < current->nodeCity->connection.size(); ++i)
        {
            location = isInOpenList(current->nodeCity->connection[i].link->name, openList);

            if (!location && !isInClosedList(current->nodeCity->connection[i].link->name, closed)){
                tempNode=new Node(current->g_prevDist+ getDistance(current->nodeCity, current->nodeCity->connection[i].link), current->nodeCity->connection[i].link, current->path, destinationCity);
                openList.push_back(tempNode);
            }
            else if (location)
            {
                tempNode=new Node(current->g_prevDist+ getDistance(current->nodeCity, current->nodeCity->connection[i].link), current->nodeCity->connection[i].link, current->path, destinationCity);
                if (tempNode->f < location->f){
                    openList.push_back(tempNode);
                    location->f=INFINITY;//pushing it deep, removing it in alternate way
                    location->g_prevDist=INFINITY;
                }
            }
        }

        sort(openList.begin(), openList.end(), sort_pred());

        closed.push_back(current);
        current=openList.back();
        openList.pop_back();
    }
    /*-----------------A* algorithm-----------------*/

    /*-----------------output-----------------------*/
    cout<<"Path: "<<current->path<<"\n"<<"cost: "<<current->g_prevDist;
    /*-----------------output-----------------------*/
}
