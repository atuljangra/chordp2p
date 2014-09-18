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
      long long toValue();
  public:
      Identifier() { };
      std::string getID() {return id;}
      Identifier(std::string id) {this->id = id; }
      ~Identifier() {};
      static Identifier * toIdentifier(std::string s);
      bool isInBetween(Identifier a, Identifier b);
      static std::string hash(std::string);
};

#endif
