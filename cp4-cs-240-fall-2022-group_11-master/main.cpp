#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include "Maxheap.h"
#include "User.h"
using namespace std;

int main(int argc, char *argv[]) {
    unordered_map<string, User> umap; //unordered map to hold users
    unordered_map<string, string> resmap;
    Maxheap* mheap = new Maxheap(); //for cravings haven't tested if works
    string command;
    User userNode; //this will be for graph later
    string username1;
    string username2;
    string restaurantName;
    string cuisine;
    string usernameforRec;
    int distance;
    int points;
    string test;

    cout << "Enter a command. Choose from " << endl;
    cout << "   CREATE <username>" << endl;
    cout << "   FRIEND <username1> <username2>" << endl;
    cout << "   UNFRIEND <username1> <username2>" << endl;
    cout << "   ADD <restaurant-name> <cuisine>" << endl;
    cout << "   REC <username> <restaurant-name>" << endl;
    cout << "   UNREC <username> <restaurant-name>" << endl;
    cout << "   CRAVE <username> <cuisine> <points>" << endl;
    cout << "   EAT <username> <friendship-distance>" << endl;
    cout << "   QUIT" << endl;
    

    while(!cin.eof()){
        cout << ": ";
        cin >> command; 
        if(command == "CREATE"){
            cin >> username1;
            //inserts a user into the hashmap, taking in <username1> as a key
            //and userNode as the value
            

            auto found = umap.find(username1);
            if( found == umap.end() ){
                userNode.setName(username1);
                //inserts a user into the hashmap, taking in <username1> as a key
                //and userNode as the value
                umap.insert( {username1, userNode} );
                //cout << "in here" << endl;
                cout << "User: " << userNode.getName() << " created." << endl; //testing
            }
            else{
                cout << "Username already in use" << endl;
            }
            //all this is doing is just looking up our key in the unordermap
            //and printing out the key value, if the key isnt found(found == umap.end)
            //then prints out not found
            // auto found = umap.find(username1);
            // if( found == umap.end() ){
            //     cout << "not found" << endl;
            //     continue;
            // }
            // else{
            //     cout << "User: " << found->first << " created." << endl;
            // }
        }

        else if(command == "FRIEND"){
            User userNode;
            cin >> username1 >> username2;
            userNode.setName(username2);
            auto found = umap.find(username1);
            if( found == umap.end() ){
                cout << "not found" << endl;
                continue;
            }
            else{
                User* userNode = &umap.at(username2);
                umap.at(username1).addFriend(userNode);
                //umap.insert( {username2, userNode} );
                //cout << found->second.friends.at(0) << endl;
            }

        }
        else if(command == "UNFRIEND"){
            cin >> username1 >> username2;
            auto found = umap.find(username1);
            if( found == umap.end() ){
                cout << "not found" << endl;
                continue;
            }
            else{
                User* userNode = &umap.at(username2);
                umap.at(username1).removeFriend(userNode);
            }

        }
        else if(command == "ADD"){
            cin >> restaurantName >> cuisine;
            resmap.insert( {restaurantName, cuisine} );
            auto found = resmap.find(restaurantName);
            if( found == resmap.end() ){
                cout << "not found" << endl;
                continue;
            }
            else{
                cout << found->first << " and " << found->second << " added." << endl;
            }
        }
        else if(command == "REC"){
            cin >> usernameforRec >> restaurantName;
            if (resmap.find(restaurantName) == resmap.end()){
                cout << restaurantName << " not found" << endl;
            }
            else{
                if(umap.find(usernameforRec) == umap.end()){
                    cout << usernameforRec << " not found" << endl;
                    continue;
                }
                else{
                    umap.at(usernameforRec).addRestaurant(restaurantName, resmap.at(restaurantName));
                }
            }
        }
        else if(command == "UNREC"){
            cin >> usernameforRec >> restaurantName;
            if (resmap.find(restaurantName) == resmap.end()){
                cout << restaurantName << " not found" << endl;
            }
            else{
                if(umap.find(usernameforRec) == umap.end()){
                    cout << usernameforRec << " not found" << endl;
                    continue;
                }
                else{
                    umap.at(usernameforRec).removeRestaurant(restaurantName);
                }
            }
        }
        else if(command == "CRAVE"){
            cin >> username1 >> cuisine >> points;
            if(username1 != "Mike"){
                cout << "Mike is the only user who can use CRAVE" << endl;
            }
            else{
                mheap->insert(cuisine, points);
            }
            //cout << mheap.getMax() << endl;
        }
        //just testing the maxheap will remove later
        else if(command == "DELMAX"){
            //string sure;
            //sure = mheap->extractMax().cuisine;
            mheap->getMax(cuisine);
            //mheap->insert(sure, 0);
            //cout << "new max: " << mheap->getMax() << endl;
        }
        else if(command == "PRINT"){
            mheap->print();
        }
        else if(command == "EAT"){
            cin >> username1 >> distance;
            if(username1 != "Mike"){
                cout << "Mike is the only user who can use CRAVE" << endl;
            }
            else{
                if(umap.at(username1).BFS(distance, mheap->getMaxCraving()) == 1){
                    string sure;
                    //sure = mheap->extractMax().cuisine;
                    mheap->getMax(sure);
                    //mheap->insert(sure, 0);
                }
            }
        }
        else if (command == "QUIT"){
            break;
        }
        else {
            cout << "command not recognized" << endl;
        }
    }
}