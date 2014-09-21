#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Node.h"

using namespace std;
int maxLen = 4;
int main(void) {
    Node *a = new Node(0);
    Node *b = new Node(3);
    Node *c = new Node(7);
    Node *d = new Node(9);
    Node *e = new Node(15);
    a -> start();
    a -> join(NULL);
    a -> printFingers(); 
   
    b -> start();
    b -> join(a);
    b -> printFingers();
    a -> printFingers();
    
    c -> start();
    d -> start();
    e -> start();
    c -> join(b);
    d -> join(c);
    e -> join(d);
    a -> printFingers();
    b -> printFingers();
    c -> printFingers();
    d -> printFingers();
    e -> printFingers();

    a -> addValueForKey("4", "Atul");
    c -> getValueForKey("4");
    return 0;
}

