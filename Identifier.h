/*
 * Identifier for various nodes.
 * This file is supposed to contain the hash functions, functions to compare
 * the two identifiers and functions of that sort.
 *
 * Should be serializable.
 *
 * We do not want to move around the Node objects. thus we have the Idenfier
 */
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <stdlib.h>
#include <string>

extern int maxLen;

class Identifier {
  private:
      std::string id;
  public:
      std::string getID() {return id;}
      Identifier() {
             
      };
      ~Identifier() {};
      // Get identifier for an object,
      // This should just call the method in the respective %sclass.
      // Implement this using abstract class.
      static Identifier getIdentifier(void *object);
      bool isInBetween(Identifier a, Identifier b);
};

#endif
