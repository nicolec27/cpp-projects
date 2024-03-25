#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Maxheap.h"
using namespace std;

//created User class for now, I think these will be the nodes in the graph for friends (might move to Graph.h later maybe idk)
//all it does is just take in a username for CREATE and makes an a User object - jason

struct restaurant{
    string name;
    string cuisine;
    restaurant(string name, string cuisine){
        this->name = name;
        this->cuisine = cuisine;
    }
};

class User{
    private:
        string name;

        vector<restaurant> recommendations;
        vector<User*> friends;
        Maxheap* mheap = new Maxheap();// add MaxHeap
    public:
        User() {name = "";};
        User(string userName) {name = userName;};

        void setName(string name);
        string getName() const;
        void addFriend(User* friend1);
        void removeFriend(User* friend1);
        void addRestaurant(string restaurantName, string cuisine);
        void removeRestaurant(string restaurantName);
        int BFS(int distance, string cravingName);

        void displayFriends();
};


#endif