#include <cstring>

#include "Node.h"
#include "utils.h"
using namespace std;
extern int maxLen;


// TODO FIX the key thing.
// TODO Add the static keys, and then use sha1 hash if you want to.
// TODO Using this keys fill in the fingerTable's start and interval entry
// while initialization
#define NULL_NODE_STRING -1

int Node::address = 0;


Node::Node() {
    // Create non-existing successor and predecessor.
    successor = new Node(NULL_NODE_STRING);
    predecessor = new Node(NULL_NODE_STRING);

    address++;
    // Create finger table.
    fingerTable = new FingerTable(maxLen);

    // Fill in the fingers with the 
}

Node::Node(int fraudID) {
    address = fraudID;
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

Identifier Node::getIdentifier() {

    // TODO STORE This identifier.
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
    if ((b->predecessor->address == NULL_NODE_STRING) || 
            a->getIdentifier().isInBetween(b->predecessor->getIdentifier(), b->getIdentifier())) {
        b->predecessor = a;
    }

}

void Node::fixFingers(int &index) {
    Finger f = fingerTable->fingers[index];
    f.node = findSuccessor(*f.start);
}

