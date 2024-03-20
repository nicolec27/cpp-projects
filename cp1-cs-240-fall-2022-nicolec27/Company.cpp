
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "Company.h"

using namespace std;

Company::Company(){
	companyName = "";
    franchises = new Franchise[1];
    arrayCapacity = 1;
    numberOfElements = 0;
}

Company& Company::operator=(const Company& other){
    // Guard self assignment
    if (this == &other)
        return *this;
    
    companyName = other.companyName;
    count = other.count;
    for (int i = 0; i < other.count; i++){
        menus[i] = other.menus[i];
    }
    delete [] franchises; // prevent memory leak
    franchises = new Franchise[other.arrayCapacity];
    for (int i = 0; i < other.numberOfElements; i++){
        franchises[i] = other.franchises[i];
    }
    arrayCapacity = other.arrayCapacity;
    numberOfElements = other.numberOfElements;

    return *this;
}

void Company::setCompanyName(string s) {
    companyName = s;
}

string Company::getCompanyName() {
    return companyName;
}

void Company::addMenu(Menu menu){
    bool found = false;
    if (count > 3){
        cout << "Menu file warning: Too many menus for company " << getCompanyName() << ". Menu " << menu.getMenuName() << " could not be added." << endl;
        //break;
    } else if (count <= 3){
        for (int i = 0; i < count; i++){
            if (menus[i].getMenuName() == menu.getMenuName()){
                found = true;
                cout << "Menu file warning: Menu " << menu.getMenuName() << " already used for company " << getCompanyName() << endl;
            }
        }
        if (found == false){
            //cout<<"Count"<<count<<endl;
            menus[count] = menu;
            count++;
            numOfMenus++;
        }
    }
}

void Company::getMenuArray(){
    //cout << "count: " << count << endl;
    for (int i = 0; i < count; i++ ) {
      cout << "    " << menus[i].getMenuName() << ":" << endl;
      menus[i].getMenuItems();
   }
}

int Company::getNumOfMenus(){
    return numOfMenus;
}

void Company::getFranchiseArray(){
    for (int i = 0; i < numberOfElements; i++ ) {
      cout << franchises[i].getFranchiseInfo() << endl;
   }
}

void Company::insert(Franchise &franchise) {
    if (numberOfElements >= arrayCapacity) {
        resize();
        franchises[numberOfElements] = franchise;
        numberOfElements++;
    } else {
        franchises[numberOfElements] = franchise;
        numberOfElements++;
    }
}

void Company::resize() {
    arrayCapacity *= 2;
    Franchise* tempFranchises = new Franchise[arrayCapacity];
    for (int i = 0; i < numberOfElements; i++) {
        tempFranchises[i] = franchises[i];
    }
    delete[] franchises;
    franchises = tempFranchises;
}
