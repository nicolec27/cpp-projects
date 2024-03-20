
#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <stdlib.h>
#include "Menu.h"
#include "Franchise.h"

using namespace std;

class Company {
    public:
        Company();
        Company& operator=(const Company& other);

        string getCompanyName();
        void setCompanyName(string s);

        void addMenu(Menu menu);
        void getMenuArray();

        Menu menus[4];
        void insert(Franchise &franchise);
        void resize();

        int getNumOfMenus();

        void getFranchiseArray();
        Franchise* franchises;


    private:
        string companyName; 
        int count = 0;

        int numOfMenus = 0;


        int arrayCapacity;
        int numberOfElements;

};

#endif