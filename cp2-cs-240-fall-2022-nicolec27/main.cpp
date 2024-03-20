#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

#include "DLL.h"

using namespace std;

int main(int argc, char *argv[]) {
    DLL mydll;
    // populate with some values
    mydll.prepend(10);
    mydll.append(20);
    mydll.append(30);
    mydll.append(40);
    mydll.append(50);
    mydll.append(60);

    DLL otherdll;
    otherdll.append(20);
    otherdll.append(50);
    otherdll.append(55);

    mydll -= otherdll;

    mydll.reset();
    int origVal;
    while (origVal = mydll.getNext()){
        cout << "[" << origVal << "]";
    }
    cout << endl;


}