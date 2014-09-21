#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Node.h"
#include "Driver.h"

#define FILENAME "insertTime.txt"
using namespace std;
int maxLen = 0;
int main(void) {
/*
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
*/
    Driver *d = new Driver();
    d -> timeAdditions(5); 
    ofstream myFile;
    myFile.open(FILENAME);
    
    for (int i = 0; i < 2000; i+=10) {
        myFile << i << " ";
    }
    myFile << endl;
    for (int i = 1; i < 2000; i+=10) {
        double time = d -> timeAdditions(i);
        myFile << time << " ";

    }
    myFile << endl;
    myFile.close();
    return 0;
}

