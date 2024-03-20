#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

using namespace std;

class MenuItem {
    public:
        MenuItem();
        MenuItem& operator=(const MenuItem& other);
        void setMICompanyName(string miconame);
        string getMICompanyName(); 
        void setMIMenuName(string miMenu);
        string getMIMenuName();
        void setMenuItemName(string menuItemstr);
        string getMenuItemName();
        void setPrice(int dollars);
        int getPrice();
        void setCalories(int cal);
        int getCalories();
        void setDescription(string desc);
        string getDescription();
        void setInfo(string min, int pr, int calo);
        string getInfo();
    private:
        string MICompanyName;
        string MIMenuName;
        string menuItemName;
        int price;
        int calories;
        string description;
        string result;
};

#endif