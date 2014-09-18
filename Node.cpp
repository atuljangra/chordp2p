#include <cstring>
#include <cmath>
#include "Node.h"
#include "utils.h"
using namespace std;
extern int maxLen;


// TODO FIX the key thing.
// TODO Add the static keys, and then use sha1 hash if you want to.
// TODO Using this keys fill in the fingerTable's start and interval entry
// while initialization
int Node::address = 0;

Node::Node() {
    // Create non-existing successor and predecessor.
    successor = new Node();
    predecessor = new Node();
    successor -> state = NODE_STATE_DEAD;
    predecessor -> state = NODE_STATE_DEAD;
    this -> state = NODE_STATE_DEAD;
    address++;
    // Create finger table.
    fingerTable = new FingerTable(maxLen);
    cout << "Node " << address << " created." << endl;
}

void Node::start() {
    cout << "Node " << address << " starting." << endl;
    // Add identifier.
    this->identifier = toIdentifier();    

    // Initialize fingers.
    long maxValue = pow(2.0, maxLen);
    long myVal = identifier.toValue();
    for (int i = 0; i < maxLen; i++) {
        long start = (long)(myVal + pow(2, i)) % maxValue;
        Finger f = fingerTable->fingers[i];
        long end = (long)(myVal + pow(2, i + 1)) % maxValue;
        f.start = Identifier::toIdentifier(to_string(start));
        f.end = Identifier::toIdentifier(to_string(end));
        f.node = this;
    }
    // Start the stabilizing thread.

    // Start the fingerfixing thread.

    // Start the predecessorCheck thread.
    
    this -> state = NODE_STATE_RUNNING;
}
    
Node* Node::findSuccessor(Identifier id) {
    // If the id is between this and it's successor.
    if (id.isInBetween(identifier, successor->getIdentifier())) {
        return successor;
    }
    // Find closest preceding node and then forward the query to that.
    else {
        Node *n = closestPrecedingNode(id);
        return n->findSuccessor(id);
    }
}

Node* Node::closestPrecedingNode(Identifier id) {
    // Scan the finger table and return the existing Node.
    for (int i = maxLen - 1; i >= 0; i--) {
        if (fingerTable->fingers[i].node->getIdentifier().isInBetween(this->getIdentifier(), id)) {
            return fingerTable->fingers[i].node;
        }
    }
    return this;
}

Node* Node::findPredecessor(Identifier id) {
    Node *n = this;
    while (!id.isInBetween(n->getIdentifier(), n->getSuccessor()->getIdentifier())) {
        n = n->closestPrecedingNode(id);
    }

    return n;
}

void Node::join(Node n) {
    predecessor = NULL;
    successor = n.findSuccessor(n.getIdentifier());
    cout << "Node " << identifier.getID() << " joined before" << 
        successor->getIdentifier().getID() << endl;
}

void Node::create() {
    predecessor = NULL;
    successor = NULL;
}

Identifier Node::toIdentifier() {
    string str = to_string(address);
    Identifier * iden = Identifier::toIdentifier(Identifier::hash(str));
    return *iden;    
}

/*
 * Stabilization Threads
 */
void Node::stabilize() {
    Node *x = successor->predecessor;
    if (x->getIdentifier().isInBetween(this->getIdentifier(), successor->getIdentifier())) {
        successor = x;
    }
    notify(successor, x);
}


void Node::notify(Node *a, Node *b) {
    // Notify successor about the change in it's predecessor.
    if ((b->predecessor->state == NODE_STATE_DEAD) || 
            a->getIdentifier().isInBetween(b->predecessor->getIdentifier(), b->getIdentifier())) {
        b->predecessor = a;
    }

}

/*
 * Finger fixing thread
 */
void Node::fixFingers(int &index) {
    Finger f = fingerTable->fingers[index];
    f.node = findSuccessor(*f.start);
}

