#include <iostream>
#include <fstream>
#include <string>

#include "Franchise.h"

using namespace std;

Franchise::Franchise(){
    franchiseNum = 0;
    companyName = "";
    phoneNumber = "";
    address = "";
}

void Franchise::setFnumber(int fnum) {
    franchiseNum = fnum;
}

int Franchise::getFnumber() {
    return franchiseNum;
}

void Franchise::setFCompanyName(string s){
    companyName = s;
}

string Franchise::getFCompanyName(){
    return companyName;
}

void Franchise::setPhoneNumber(string num){
    phoneNumber = num;
}

string Franchise::getPhoneNumber(){
    return phoneNumber;
}

void Franchise::setAddress(string addr){
    address = addr;
}

string Franchise::getAddress(){
    return address;
}

void Franchise::setFranchiseInfo(){
  fstr = "    " + getFCompanyName() + " #" + to_string(getFnumber()) + ", at " + getAddress() + " " + getPhoneNumber();
}

string Franchise::getFranchiseInfo(){
  return fstr;
}