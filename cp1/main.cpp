#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Company.h"

using namespace std;

Company* companies = new Company[1];
int arrayCapacity = 1;
int numberOfElements = 0;
void resize() {
    arrayCapacity *= 2;
    Company* tempItems = new Company[arrayCapacity];
    for (int i = 0; i < numberOfElements; i++) {
        tempItems[i] = companies[i];
    }
    delete[] companies;
    companies = tempItems;
}

int main(int argc, char *argv[]) {
    ifstream cotxt;
    cotxt.open("companies.txt");
    Company temp;   // To read each line from code
    string s = "";
    while(!cotxt.eof())
    {
        if (numberOfElements < arrayCapacity){
            getline(cotxt, s);
            temp.setCompanyName(s);
            companies[numberOfElements]=temp;
            numberOfElements++;
        } else{
            resize();
            getline(cotxt, s);
            temp.setCompanyName(s);
            companies[numberOfElements]=temp;
            numberOfElements++;
        }
    }
    cotxt.close();
    /*
    for (int j = 0; j < numberOfElements; j++){
        cout << companies[j].getCompanyName() << endl;
    }
    */
    ifstream menutxt;
    menutxt.open("menus.txt");
    Menu mtemp;
    bool found = false;
    while(!menutxt.eof()){
        string companyName;
        string menuName;

        menutxt >> companyName;
        menutxt >> menuName;

        mtemp.setCompName(companyName);
        mtemp.setMenuName(menuName);
        string str = mtemp.getCompName();

        found = false;
        for (int j =0; j < numberOfElements; j++){
            string str2 = companies[j].getCompanyName();
            if (str == str2){
                found = true;
                companies[j].addMenu(mtemp);
            }
            
        }
        if (found == false){
            cout << "Menu file warning: Company " << mtemp.getCompName() <<  " does not exist." << endl;
            continue;
        }
    }
    menutxt.close();

    ifstream menuitemstxt;
    menuitemstxt.open("menu_items.txt");
    while(!menuitemstxt.eof()){
        MenuItem mitemp;
        string companyName;
        string menuName;
        string itemName;
        string price;
        string calories;
        string description;

        menuitemstxt >> companyName;
        menuitemstxt >> menuName;
        menuitemstxt >> itemName;
        menuitemstxt >> price;
        menuitemstxt >> calories;
        getline(menuitemstxt, description);


        mitemp.setMICompanyName(companyName);
        // cout << mitemp.getMICompanyName() << endl;
        mitemp.setMIMenuName(menuName);
        //cout << mitemp.getMIMenuName() << endl;
        mitemp.setMenuItemName(itemName);
        //cout << mitemp.getMenuItemName() << endl;
        mitemp.setPrice(stoi(price));
        //cout << mitemp.getPrice() << endl;
        mitemp.setCalories(stoi(calories));
        //cout << mitemp.getCalories() << endl;
        mitemp.setDescription(description);
        // cout << mitemp << endl;
        mitemp.setInfo(itemName, stoi(price), stoi(calories));
        //cout << mitemp.getInfo() << endl;
        //cout << "       " << description << endl;
        found = false;
        bool mfound = false;
        bool matchMI = false;
        for (int a = 0; a < numberOfElements; a++){
            if (companies[a].getCompanyName() == mitemp.getMICompanyName()){
                //cout << "company here: " << companies[a].getCompanyName() << endl;
                found = true;
                //cout << "num of menus: " << companies[a].getNumOfMenus() << endl;
                for (int b = 0; b < 4; b++){
                    if (companies[a].menus[b].getMenuName() == mitemp.getMIMenuName()){
                        mfound = true;
                        matchMI = companies[a].menus[b].matchMenuItem(mitemp);
                        if (matchMI == true){
                            cout << "Menu item file warning: Item " << mitemp.getMenuItemName() << " already present in " << mitemp.getMIMenuName() << " of company " << mitemp.getMICompanyName() << endl;
                            continue;
                        } 
                        resize();
                        companies[a].menus[b].insert(mitemp);
                        //cout << companies[a].getCompanyName() << " " << companies[a].menus[b].getMenuName() << endl;
                    } 
                }
                if (mfound == false){
                    cout << "Menu item file warning: Company " << mitemp.getMICompanyName() <<  " does not have a menu named " << mitemp.getMIMenuName() << endl; 
                    continue;
                }
                
            }
            
        }
        if (found == false){
            cout << "Menu item file warning: Company " << mitemp.getMICompanyName() <<  " does not exist." << endl; 
            continue;
        }      
    }
    menuitemstxt.close();

    // for (int a = 0; a < i-1; a++){
    //     cout << " -------. " << companies[a].getCompanyName() << endl;
    //     for (int b = 0; b < 4; b++){
    //         cout << companies[a].menus[b].getMenuName() << endl;
    //     }
    // }   

    ifstream franchisetxt;
    franchisetxt.open("franchises.txt");
    while(!franchisetxt.eof()){
        //cout << "restart" << endl;
        Franchise ftemp;
        string what;
        string companyName;
        string phonenum;
        string address;

        franchisetxt >> what;
        franchisetxt >> companyName;
        franchisetxt >> phonenum;
        getline(franchisetxt, address);

        ftemp.setFnumber(stoi(what));
        ftemp.setFCompanyName(companyName);
        ftemp.setPhoneNumber(phonenum);
        // cout << mitemp << endl;
        ftemp.setAddress(address);
        //cout << mitemp.getInfo() << endl;
        //cout << "       " << description << endl;
        ftemp.setFranchiseInfo();
        found = false;
        for (int a = 0; a < numberOfElements; a++){
            if (companies[a].getCompanyName() == ftemp.getFCompanyName()){
                //cout << "company here: " << companies[a].getCompanyName() << endl;
                found = true;
                //cout << "num of menus: " << companies[a].getNumOfMenus() << endl;
                resize();
                companies[a].insert(ftemp);
                //cout << ftemp.getFranchiseInfo() << endl;
            }
            
        }
        if (found == false){
            cout << "Franchise file warning: Company " << ftemp.getFCompanyName() <<  " does not exist." << endl; 
            continue;
        }      
    }
    franchisetxt.close();

    for (int z = 0; z < numberOfElements; z++){
            cout << companies[z].getCompanyName() << ":" << endl;
            cout << "  Menus:" << endl;
            companies[z].getMenuArray();
            //cout << "num of menus: " << companies[z].getNumOfMenus() << endl;
            // for (int g = 0; g < companies[z].getNumOfMenus(); g++){
            //     cout << "     " << companies[z].menus[g].getMenuName() << ":" << endl;
            //     companies[z].menus[g].getMenuItems();
            // }
            cout << "  Franchises:" << endl;
            companies[z].getFranchiseArray();
            cout << endl;
    }

}