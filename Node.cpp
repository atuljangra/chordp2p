#include <cstring>

#include "Node.h"
#include "utils.h"
using namespace std;
extern int maxLen;


// TODO FIX the key thing.
// TODO Add the static keys, and then use sha1 hash if you want to.
// TODO Using this keys fill in the fingerTable's start and interval entry
// while initialization
#define NULL_NODE_STRING "null"
#define NULL_PORT -1
Node::Node() {
    successor = new Node(NULL_NODE_STRING);
    predecessor = new Node(NULL_NODE_STRING);
    address = NULL_NODE_STRING;
    port = NULL_PORT;
    fingerTable = new FingerTable(maxLen);
}

Node::Node(string s) {
    successor = new Node(NULL_NODE_STRING);
    predecessor = new Node(NULL_NODE_STRING);
    port = NULL_PORT;
    fingerTable = new FingerTable(maxLen);
    address = s;
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
    char *str = new char[address.length() + 1];
    strcpy(str, address.c_str());
    strcat(str, ":");
    strcat(str, to_string(port).c_str());
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
    if (b->predecessor->address.compare(NULL_NODE_STRING) || 
            a->getIdentifier().isInBetween(b->predecessor->getIdentifier(), b->getIdentifier())) {
        b->predecessor = a;
    }

}

void Node::fixFingers(int &index) {
    Finger f = fingerTable->fingers[index];
    f.node = findSuccessor(*f.start);
}

