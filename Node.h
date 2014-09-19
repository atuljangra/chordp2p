/*
 * This is the file corresponding to each node in the chord.
 * We will create instances of this to simulate various nodes.
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <thread>
#include "Identifier.h"

#define NODE_STATE_RUNNING 1 
#define NODE_STATE_DEAD 2
class FingerTable; 
class Node {
  private:  
      Identifier *identifier;  
      Node *predecessor;
      Node *successor;
      FingerTable *fingerTable;
      std::thread _stabilize;
      std::thread _fixFinger;
      Identifier *toIdentifier();
      int state;
      void stabilize();
      void fixFingers(int index);

  public:
    static int address;
    // This constructure is meant to be used.
    Node();
    ~Node();
    void start();
    Identifier *getIdentifier() {return identifier;}
    Node * findSuccessor(Identifier *id);
    Node * findPredecessor(Identifier *id);
    Node * closestPrecedingNode(Identifier *id);
    void join(Node *n);
    void create();
    
    Node * getSuccessor() {return successor;}
    Node * getPredecessor() {return predecessor;}
    
    void stabilizeThread();
    // index that we want to fix.
    void fixFingersThread();

    /*
     * Function for notifyinh nodes.
     * Node a notifies Node b about itself.
     */ 
    static void notify(Node *a, Node *b);
};

// This is important here.
#include "FingerTable.h"

#endif 
