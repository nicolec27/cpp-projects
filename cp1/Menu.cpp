#include <iostream>
#include <fstream>
#include <string>

#include "Menu.h"

using namespace std;

Menu::Menu(){
    companyName = "";
	menuName = "";
    menuItems = new MenuItem[1];
    arrayCapacity = 1;
    numberOfElements = 0;
}

Menu& Menu::operator=(const Menu& other){
    // Guard self assignment
    if (this == &other)
        return *this;

    companyName = other.companyName;
    menuName = other.menuName;
    //menuItems = other.menuItems;
    delete [] menuItems; // prevent memory leak
    menuItems = new MenuItem[other.arrayCapacity];
    for (int i = 0; i < other.numberOfElements; i++){
        menuItems[i] = other.menuItems[i];
    }
    arrayCapacity = other.arrayCapacity;
    numberOfElements = other.numberOfElements;

    return *this;
}


void Menu::setMenuName(string s) {
    menuName = s;
}

string Menu::getMenuName() {
    return menuName;
}

void Menu::setCompName(string c) {
    companyName = c;
}

string Menu::getCompName() {
    return companyName;
}

void Menu::insert(MenuItem &itemToInsert) {
    //cout << "num of elements: " << numberOfElements << endl;
    //cout << arrayCapacity << endl;
    if (numberOfElements >= arrayCapacity) {
        resize();
        menuItems[numberOfElements] = itemToInsert;
        numberOfElements++;
    } else {
        menuItems[numberOfElements] = itemToInsert;
        numberOfElements++;
    }
}

void Menu::resize() {
    arrayCapacity *= 2;
    MenuItem* tempItems = new MenuItem[arrayCapacity];
    for (int i = 0; i < numberOfElements; i++) {
        tempItems[i] = menuItems[i];
    }
    delete[] menuItems;
    menuItems = tempItems;
}

void Menu::getMenuItems(){
    //cout << "num of elems: " << numberOfElements << endl;
    for (int i = 0; i < numberOfElements; i++) {
        if (menuName == menuItems[i].getMIMenuName()){
            cout << menuItems[i].getInfo() << endl;
            cout << "       " << menuItems[i].getDescription() << endl;
        }
        
    }
}

bool Menu::matchMenuItem(MenuItem menuItem){
    bool match = false;
    for (int i = 0; i < numberOfElements; i++) {
        if (menuItem.getMenuItemName() == menuItems[i].getMenuItemName()){
            match = true;
            break;
        }
        match = false;
    }
    return match;

}
