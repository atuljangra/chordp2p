#include <cstring>

#include "Node.h"
#include "utils.h"
using namespace std;
extern int maxLen;
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
