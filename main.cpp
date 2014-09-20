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
    Node *c = new Node();
    c -> start();
    c -> join(a);
    b -> join(a);
    a -> printFingers();
    b -> printFingers();
    c -> printFingers();
    return 0;
}

