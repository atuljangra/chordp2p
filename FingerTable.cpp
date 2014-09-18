#include "FingerTable.h"
#include <iostream>
using namespace std;

FingerTable::FingerTable(int count) {
   fingers = new Finger[count];
   length = count;
   
}

void FingerTable::print() {
    for (int i = 0; length; i++) {
        cout << i << ":Start:" << fingers[i].start->getID() << " end:" 
            <<fingers[i].end->getID() << endl;
    }

}
