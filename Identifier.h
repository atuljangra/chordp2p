/*
 * Identifier for various nodes.
 * This file is supposed to contain the hash functions, functions to compare
 * the two identifiers and functions of that sort.
 *
 * Should be serializable.
 */

#include <iostream>
#include "Node.h"
class Identifier {
  public:
    Identifier() {};
    ~Identifier() {};

    // Get identifier for an object,
    // This should just call the method in the respective class.
    // Implement this using abstract class.
    static Identifier getIdentifier(void *object);


};

