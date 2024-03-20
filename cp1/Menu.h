#ifndef MENU_H
#define MENU_H

#include <string>
#include "MenuItem.h"

using namespace std;

class Menu {
    public:
        Menu();
        Menu& operator=(const Menu& other);
        void setMenuName(string s);
        string getMenuName();
        void setCompName(string c);
        string getCompName();
        void insert(MenuItem &MenuItem);
        void resize();
        void getMenuItems();
        bool matchMenuItem(MenuItem menuItem);

    private:
        string menuName;
        string companyName;

        int numberOfElements;
        int arrayCapacity;
        MenuItem* menuItems;

};

#endif