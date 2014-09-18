/*
 * This is the file corresponding to each node in the chord.
 * We will create instances of this to simulate various nodes.
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include "Identifier.h"

class FingerTable; 
class Node {
  private:  
      Identifier identifier;  
      Node *predecessor;
      Node *successor;
      FingerTable *fingerTable;

  public:
    static int address;
    // This constructure is meant to be used.
    Node();

    // This is used to simulate non-existing nodes.
    Node(int fraudID);
    Identifier getIdentifier();
    Node * findSuccessor(Identifier id);
    Node * findPredecessor(Identifier id);
    Node * closestPrecedingNode(Identifier id);
    void join(Node n);
    void create();
    
    Node * getSuccessor() {return successor;}
    Node * getPredecessor() {return predecessor;}
    
    void stabilize();
    // index that we want to fix.
    void fixFingers(int &index);

    /*
     * Function for notifyinh nodes.
     * Node a notifies Node b about itself.
     */ 
    static void notify(Node *a, Node *b);
};

// This is important here.
#include "FingerTable.h"

#endif 
