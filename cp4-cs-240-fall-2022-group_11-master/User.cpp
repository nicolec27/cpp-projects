#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include <unordered_set>
#include <assert.h>
#include "User.h"
using namespace std;


void User::setName(string username){
    name = username;
}

string User::getName() const{
    return name;
}

void User::addFriend(User* friend1){
    friends.push_back(friend1);
    for (int i=0; i < friends.size(); i++) {
        cout << friends.at(i)->name << endl;
    }
}

void User::removeFriend(User* friend1){
    // cout << "friends at index 0: " << friends.at(0).name << endl;
    for (int i=0; i < friends.size(); i++) {
        if (friends.at(i) == friend1){
            friends.erase(friends.begin()+i);
            return;
        }
    }
}

void User::addRestaurant(string restaurantName, string cuisine){
    recommendations.emplace_back(restaurantName, cuisine);
    for (int i=0; i < recommendations.size(); i++) {
        cout << recommendations.at(i).name << endl;
    }
}

void User::removeRestaurant(string restaurantName){
    // cout << "friends at index 0: " << friends.at(0).name << endl;
    for (int i=0; i < recommendations.size(); i++) {
        if (recommendations.at(i).name == restaurantName){
            recommendations.erase(recommendations.begin()+i);
            return;
        }
    }
}

int User::BFS(int distance, string cravingName){
    int distanceSoFar = 0;
    list<User*> frontierQueue;
    list<User*> discoveredSet;
    unordered_set<User*> set;

    frontierQueue.push_back(this);
    
    User* currentUser;
    while (!frontierQueue.empty() && distanceSoFar <= distance) {
        //while(!frontierQueue.empty()){
            currentUser = frontierQueue.front();
            frontierQueue.pop_front();
            //currentUser = frontierQueue.pop_front();
            assert(currentUser);
            //cout << "current user: " << currentUser->name << endl;
            //cout << currentUser << " current" << endl;
            //auto currentUser = frontierQueue.begin();
            //cout << "user " << currentUser->name << " has " << currentUser->recommendations.size() << " restaurant recommendations" << endl;
            for (auto rest : currentUser->recommendations){
                if(rest.cuisine == cravingName){
                    cout << currentUser->name << " recommends eating at " << rest.name << endl;
                    cout << currentUser->name << " is " << distanceSoFar << " friend(s) away." << endl;
                    //cout << rest.name << " is being considered" << endl;
                    return 1;
                    //cout << rest.name << endl;
                }
            }
            //cout << "Couldn't find a recommendation from " << currentUser->name << endl;
            for (auto adj : currentUser->friends){ 
                if(set.find(adj) == set.end()){
                    //frontierQueue.push_back(adj);
                    discoveredSet.push_back(adj);
                    set.insert(adj);
                    
                }
            }
        //}
        frontierQueue.swap(discoveredSet);
        distanceSoFar++;
        //cout << "distance " << distanceSoFar << endl;
    }
    cout << "Couldn't find any restaurants recommended :(" << endl;
    return 0;
}

void User::displayFriends(){/*
    for (auto x : map){ //is this right? no clue.
        recommendations.push_back(x.first);
        friends.push_back(x.second);
    }*/
}


// BFS
    // eat is called with friendship distance (if it is 1, friend) (if 2, friend of a friend)
    // recommendation of the restaurant


// one user is going to have different cravings
    // when eat is called, take the food that is being craved the most (top craving), 
    // max heap take top craving and remake heap for the second craving to be the top