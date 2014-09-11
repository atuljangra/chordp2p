/*
 * This is the interfacet that is implemented by each Node.
 */
#include <iostream>
#include "Identifier.h"

using namespace std;

template<typename T>
class NodeInterface {
  public:
    NodeInterface() {};  
    virtual T findSuccessor(Identifier id)=0;
    virtual T findPredecessor(Identifier id)=0;
    virtual T getPredecessor(Identifier id)=0;
    virtual T getSuccessor(Identifier id)=0;

    virtual bool notify(T node)=0;
    virtual T closestPrecedingFinger(Identifier id)=0;
    virtual bool exists();
    

    // Virtual Destructor.
    virtual ~NodeInterface() {};
};


