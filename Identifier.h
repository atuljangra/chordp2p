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
      // Hashed key
      std::string id;
  public:
      long toValue();
      Identifier() {};
      std::string getID() {return id;}
      Identifier(std::string id) {this->id = id; }
      ~Identifier() {};
      static Identifier * toIdentifier(std::string s);
      /*
       * return true if this is in between a and b, with a being the lower
       * bound and b being the upper.
       */
      bool isInBetween(Identifier *a, Identifier *b, int leftClosed, int rightClosed);
      static std::string hash(std::string);
};

#endif
