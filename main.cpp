#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Node.h"

using namespace std;
int maxLen = 3;
int main(void) {
    Node *a = new Node(0);
    a->start();
    a -> join(NULL);
    a -> printFingers(); 
   
    Node *b = new Node(5);
    b -> start();
    b -> join(a);
    b -> printFingers();
    a -> printFingers();
    cout << "Succ for A is " << a -> getSuccessor() -> getIdentifier() -> toValue() << endl;
    
    Node *c = new Node(3);
    c -> start();
    c -> join(b);
    
    a -> printFingers();
//    Node *d1 = new Node();
//    Node *d2 = new Node();
//    Node *f = new Node();
//    f -> start();
//    f -> join(a);
//    a -> printFingers();
    b -> printFingers();
    c -> printFingers();
//    f -> printFingers();
    return 0;
}

