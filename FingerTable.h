#ifndef FINGERTABLE_H_
#define FINGERTABLE_H_

#include "Identifier.h"
#include "Node.h" 

class Finger {
    public:
        Identifier *start;
        Identifier *end;
        Node *node;
        Finger() {
        }

        ~Finger() {
        }

};


class FingerTable {
    public:
       int length;
       Finger *fingers;
       FingerTable(int count);
       void print();
       
};

#endif
