/*
 * This is the file corresponding to each node in the chord.
 * We will create instances of this to simulate various nodes.
 */
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <thread>
#include <unordered_map>
#include "Identifier.h"

#define NODE_STATE_RUNNING 1 
#define NODE_STATE_DEAD 2
class FingerTable; 
class Node {
  private: 
      std::unordered_map<std::string, std::string> keyMap; 
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
      int address;
      static long messageCount;
  public:
    Node(int address);
    ~Node();
    
    // This function should be called before doing any other operation. 
    void start();
    Identifier *getIdentifier() {return identifier;}
    Node * findSuccessor(Identifier *id);
    Node * findPredecessor(Identifier *id);
    Node * closestPrecedingNode(Identifier *id);
    void concurrentJoin(Node *n);
    void join(Node *n);
    void create();
    
    Node * getSuccessor() {return successor;}
    Node * getPredecessor() {return predecessor;}
    
    void stabilizeThread();
    // index that we want to fix.
    void fixFingersThread();
    
    void initFingerTable(Node *n);
    
    /*
     * Update all nodes whose finger tables should refer to this node.
     */
    void updateOthers();
    
    /*
     * If Node s is the ith finger of this Node, then update this node's finger
     * table with Node s.
     */
    void updateFingerTable(Node *s, int i);
    /*
     * Function for notifyinh nodes.
     * Node a notifies Node b about itself.
     */ 
    static void notify(Node *a, Node *b);
    void printFingers();


    /*
     * Distributed hash table operations.
     */
    void addValueForKey(std::string key, std::string value);
    std::string getValueForKey(std::string key);
    void removeValueForKey(std::string key);
    void printKeysAndFingers();

    static void resetMessageCount();
    static long getMessageCount();
     
};

// This is important here.
#include "FingerTable.h"

#endif 
