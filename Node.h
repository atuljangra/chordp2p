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
      std::string address;
      int port;
      FingerTable *fingerTable;

  public:
    Node() {
    }
    Identifier getIdentifier() {return identifier;}
    Node * findSuccessor(Identifier id);
    Node * findPredecessor(Identifier id);
    Node * closestPrecedingNode(Identifier id);
    void join(Node n);
    void create();
};

// This is important here.
#include "FingerTable.h"

#endif 
