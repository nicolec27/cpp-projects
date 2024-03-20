#include <iostream>
#include <fstream>
#include <string>

#include "MenuItem.h"

using namespace std;

MenuItem::MenuItem(){
  MICompanyName = "";
  MIMenuName = "";
	menuItemName = "";
  price = 0;
  calories = 0;
  description = "";
  result = "";
}

MenuItem& MenuItem::operator=(const MenuItem& other){
    // Guard self assignment
    if (this == &other)
        return *this;

    MICompanyName = other.MICompanyName;
    MIMenuName = other.MIMenuName;
    menuItemName = other.menuItemName;
    price = other.price;
    calories = other.calories;
    description = other.description;
    result = other.result;

    return *this;
}

void MenuItem::setMICompanyName(string miconame){
  MICompanyName = miconame;
}

string MenuItem::getMICompanyName() {
    return MICompanyName;
}

void MenuItem::setMIMenuName(string miMenu){
  MIMenuName = miMenu;
}

string MenuItem::getMIMenuName(){
  return MIMenuName;
}

void MenuItem::setMenuItemName(string menuItemstr){
  menuItemName = menuItemstr;
}

string MenuItem::getMenuItemName(){
  return menuItemName;
}
void MenuItem::setPrice(int dollars){
  price = dollars;
}

int MenuItem::getPrice(){
  return price;
}

void MenuItem::setCalories(int cal){
  calories = cal;
}

int MenuItem::getCalories(){
  return calories;
}

void MenuItem::setDescription(string desc){
  description = desc;
}

string MenuItem::getDescription(){
  return description;
}

void MenuItem::setInfo(string menuItemName, int price, int calories){
  result = "      " + menuItemName + " $" + to_string(price) + ".00 " + to_string(calories) + " calories";
}

string MenuItem::getInfo(){
  return result;
}
