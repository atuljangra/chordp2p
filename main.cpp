#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Node.h"

using namespace std;
int maxLen = 5;
int main(void) {
    Node *a = new Node();
    a->start();
    a->create();
    Node *b = new Node();
    b -> start();
    Node *c = new Node();
    c -> start();
    c -> join(a);
    b -> join(a);
    return 0;
}

