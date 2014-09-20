#include <cstring>
#include <cmath>
#include <unistd.h>
#include <assert.h>

#include "Node.h"
#include "utils.h"

#define CONCURRENT 0
#define NAME getIdentifier() -> getID()

using namespace std;

unsigned int stabilizeSleepTime = 400; //microseconds
unsigned int fixFingerSleepTime = 1000; //microseconds
extern int maxLen;

int Node::address = -1;

Node::Node(int ad) {
    // Create non-existing successor and predecessor.
    cout << "Address is " << address << endl;
    this -> state = NODE_STATE_DEAD;
    address = ad;;
    cout << "Node " << address << " created." << endl;
}

void Node::start() {
    cout << "Node " << address << " starting." << endl;
   
    
    successor = this;

    // Add identifier.
    this->identifier = toIdentifier();    

    // Create finger table.
    fingerTable = new FingerTable(maxLen);
    fingerTable -> name = NAME; 
    // Initialize fingers.
    long maxValue = pow(2.0, maxLen);
    long myVal = identifier->toValue();
    for (int i = 0; i < maxLen; i++) {
        long start = (long)(myVal + pow(2, i)) % maxValue;
        long end = (long)(myVal + pow(2, i + 1)) % maxValue;
        fingerTable->fingers[i].start = Identifier::toIdentifier(to_string(start));
        fingerTable->fingers[i].end = Identifier::toIdentifier(to_string(end));
        // The node in the fingers would be set later.
    }

    if (CONCURRENT) {
        // Start the stabilizing thread.
        _stabilize = thread(&Node::stabilizeThread, this);
    
        // Start the fingerfixing thread.
        _fixFinger = thread(&Node::fixFingersThread, this);
        // Start the predecessorCheck thread.
    }

    this -> state = NODE_STATE_RUNNING;
    // cout << "Node " << address << " is node " << identifier -> getID() << endl; 
}

Node::~Node() {
    delete predecessor;
    delete successor;
    delete fingerTable;
}

Node* Node::findSuccessor(Identifier *id) {
    // If the id is between this and it's successor
    cout << "checking " << id->getID() << " between " 
        << identifier->getID() << " and " << successor->getIdentifier()->getID() << endl;
    if (id->isInBetween(identifier, successor->getIdentifier(), 0, 1)) {
        cout << "Is in between" << endl;
  //      return successor;
    }
    /*
    // Find closest preceding node and then forward the query to that.
    else {
        Node *n = closestPrecedingNode(id);
        cout << NAME << " closest preceding node to " << id->toValue() << " is " << n->NAME << endl;
        return n->findSuccessor(id);
    }
    */
    Node *n = findPredecessor(id);
    Node *k = n -> getSuccessor();
    cout << "Successor for " << id->toValue() << " is " << k->NAME << endl;
    return k;
}

Node* Node::closestPrecedingNode(Identifier *id) {
    // Scan the finger table and return the existing Node.
    cout << NAME << " finding closet preceding node to " << id -> getID() << endl;
    for (int i = maxLen - 1; i >= 0; i--) {
        cout << "Finding if " << fingerTable->fingers[i].node->NAME << " is in between " << NAME << " and " <<
            id -> toValue() << endl;
        if (fingerTable->fingers[i].node->getIdentifier()->isInBetween(
                    this->getIdentifier(), id, 0, 0)) {
            cout << "Closest pred node is " << fingerTable->fingers[i].node->NAME << endl;
            return fingerTable->fingers[i].node;
        }
    }
    cout << " I am the CPF " << endl;
    return this;
}

Node* Node::findPredecessor(Identifier *id) {
    Node *n = this;
    while (!id->isInBetween(n->getIdentifier(), n->getSuccessor()->getIdentifier(),0, 0)) {
        cout << id -> toValue() << " is not in between " << n -> NAME << " and " <<
            n -> getSuccessor()-> NAME << endl;
        Node *k = n->closestPrecedingNode(id);
        if (k == n)
            break;
        else 
            n = k;
    }
        cout << id -> toValue() << " is in between " << n -> NAME << " and " <<
            n -> getSuccessor()-> NAME << endl;
    cout << "pred for " << id->toValue() << " is " << n->NAME << endl;
    return n;
}

void Node::concurrentJoin(Node *n) {
    predecessor = NULL;
    successor = n->findSuccessor(n->getIdentifier());
    cout << "Node " << identifier->getID() << " joined before " <<
        successor->getIdentifier()->getID() << endl;
    if (CONCURRENT) 
        return;


}

void Node::join(Node *n) {
    // Assert to ensure that the node is running.
    assert(this->state = NODE_STATE_RUNNING);

    // Am I the only one round here?
    if (n == NULL) {
        cout << "Starting a new ring with " << NAME << endl;
        for (int i = 0; i < maxLen; i++) {
            fingerTable->fingers[i].node = this;
        }
        predecessor = this;
    }
    else {
        cout << NAME << " trying to join " << n->NAME << endl;
        initFingerTable(n);
        cout << "Initialized finger table " << NAME << endl;
        printFingers();
        updateOthers();
        cout << NAME << " joined " << n->NAME << endl;

    }

}

void Node::initFingerTable(Node *n) {
    fingerTable->fingers[0].node = n->findSuccessor(fingerTable->fingers[0].start);
    // This is obvious.
    successor = fingerTable->fingers[0].node;
    predecessor = successor->predecessor;
    cout << "Setting suc: " << successor->NAME << " pred: " << predecessor->NAME << endl;
    successor->predecessor = this;
    // Verify the above using gdb;
    for (int i = 0; i < maxLen - 1; i++) {
        cout << fingerTable->fingers[i+1].start->toValue() << " between " << identifier->toValue() << " and "
            << fingerTable->fingers[i].node->NAME << endl;
        if (fingerTable->fingers[i+1].start->isInBetween(
                    identifier, fingerTable->fingers[i].node->getIdentifier(), 1, 0)) {
            fingerTable->fingers[i+1].node = fingerTable->fingers[i].node;
            cout << "setting " << i + 1 << " to " << fingerTable->fingers[i].node->NAME << endl;
        }
        else {
            fingerTable->fingers[i+1].node = 
                n->findSuccessor(fingerTable->fingers[i+1].start);
            cout << "ELSE setting " << i + 1 << " to " << fingerTable->fingers[i].node->NAME << endl;
        }
    }
}

void Node::updateOthers() {
    long maxValue = pow(2.0, maxLen);
    for (int i = 0; i < maxLen; i++) {
        long power = pow(2.0, i);
        long myVal = identifier->toValue();
        myVal = (myVal < power) ? (myVal + maxValue) : myVal;
        // find the last node p whose ith finger might be n.
        Identifier *iden = Identifier::toIdentifier(
                to_string(myVal - power));
        cout << NAME << " finding pred for " << iden->toValue() << endl;
        Node *pred = findPredecessor(iden);
        cout << "pred is " << pred->NAME << endl;
        // TODO remove this check.
       // if (pred != this)
            pred -> updateFingerTable(this, i);
    }

}

void Node::updateFingerTable(Node *s, int i) {
    cout << NAME << " updating finger " << i << " with " << s-> NAME <<  endl;
    cout << "finding if " << s->NAME << " is in b/w " << NAME <<  " " << fingerTable->fingers[i].node->NAME << endl;
    if (s->getIdentifier()->isInBetween(identifier, 
                fingerTable->fingers[i].node->getIdentifier(), 1, 0)) {
        cout << "Updating finger " << NAME << endl;  
        // if we are updating the first finger, then we should also update the successor.
        if (i==0) {
            successor = s;
        }

        fingerTable->fingers[i].node = s;
        Node *pred = predecessor;
        pred -> updateFingerTable(s, i);
    }

}

void Node::printFingers() {
    fingerTable->print();
}

void Node::create() {
    predecessor = NULL;
}

Identifier *Node::toIdentifier() {
    string str = to_string(address);
    return Identifier::toIdentifier(Identifier::hash(str));
}

/*
 * Stabilization Threads
 */
void Node::stabilize() {
    Node *x = successor->predecessor;
    cout << "stabilizing " << identifier -> getID() << endl;
    if (x != NULL && x->getIdentifier()->isInBetween(
                this->getIdentifier(), successor->getIdentifier(), 0, 1)) {
        successor = x;
        cout << "Node " << identifier->getID() << " changed successor to "
            << x->getIdentifier()->getID() << endl;
    }
    if (x == NULL) 
        // Don't bother notifying the other node.
        return;
    notify(successor, x);
}

void Node::stabilizeThread() {
    while(true) {
        stabilize();
        usleep(stabilizeSleepTime);
    }
}

void Node::notify(Node *a, Node *b) {
    // Notify successor about the change in it's predecessor.
    cout << "Notify " << a->getIdentifier() -> getID() << endl;
    if (b -> predecessor == NULL) {
        b->predecessor = a;
        cout << " Changing predecessor of " << b->getIdentifier()->getID() << " to " << 
            a -> getIdentifier() -> getID() << endl;
        return;
    }

    if ((b->predecessor->state == NODE_STATE_DEAD) || 
            a->getIdentifier()->isInBetween(
                b->predecessor->getIdentifier(), b->getIdentifier(), 0, 1)) {
        b->predecessor = a;
        cout << " Changing predecessor of " << b->getIdentifier()->getID() << " to " << 
            a -> getIdentifier() -> getID() << endl;
    }

}

/*
 * Finger fixing thread
 */
void Node::fixFingers(int index) {
    Finger f = fingerTable->fingers[index];
    f.node = findSuccessor(f.start);
}

void Node::fixFingersThread() {
    int i = 0;
    while(true) {
        fixFingers(i);
        i = (i + 1)%maxLen;
        usleep(fixFingerSleepTime);
    }

}

