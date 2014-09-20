#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Node.h"

using namespace std;
int maxLen = 3;
int main(void) {
    Node *a = new Node();
    a->start();
    a -> join(NULL);
    a -> printFingers(); 
   
    Node *b = new Node();
    b -> start();
    b -> join(a);
    b -> printFingers();
    a -> printFingers();
    Node *d = new Node();
    
    Node *c = new Node();
    c -> start();
    c -> join(a);
    a -> printFingers();
    Node *d1 = new Node();
    Node *d2 = new Node();
    Node *f = new Node();
    f -> start();
    f -> join(a);
    a -> printFingers();
    b -> printFingers();
    c -> printFingers();
    f -> printFingers();
    return 0;
}

