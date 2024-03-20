#ifndef FRANCHISE_H
#define FRANCHISE_H

#include <string>

using namespace std;

class Franchise {
    public:
        Franchise();
        void setFnumber(int fnum);
        int getFnumber();
        void setFCompanyName(string s);
        string getFCompanyName();
        void setPhoneNumber(string num);
        string getPhoneNumber();
        void setAddress(string addr);
        string getAddress();
        void setFranchiseInfo();
        string getFranchiseInfo();


    private:
        int franchiseNum;
        string companyName;
        string phoneNumber;
        string address;

        string fstr;

};

#endif