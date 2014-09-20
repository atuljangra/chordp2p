#include "FingerTable.h"
#include <iostream>
using namespace std;

FingerTable::FingerTable(int count) {
   fingers = new Finger[count];
   length = count;
   
}

void FingerTable::print() {
    cout << "------" << endl;
    cout << "Finger table for " << name << endl;

    for (int i = 0; i < length; i++) {
        cout << i << " :Start: " << fingers[i].start->getID() << " end:" 
            <<fingers[i].end->getID() << " Node:" << 
            fingers[i].node->getIdentifier()->getID() << endl;
    }
    cout << "------" << endl;

}
