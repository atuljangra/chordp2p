#include "Identifier.h"
#include <math.h>
#include <assert.h>
#include <openssl/sha.h>
#include <iostream>

using namespace std;

// Closed interval at larger one.
bool Identifier::isInBetween(Identifier *a, Identifier *b) {
    long valA = a->toValue();
    long valB = b->toValue();

    long larger = (valA >= valB) ? valA : valB;
    long smaller = (valA < valB) ? valA : valB;

    if (valA == valB)
        return true;
    long val = this->toValue();
    return (val > smaller) && (val <= larger); 
}

Identifier * Identifier::toIdentifier(string s) {
    Identifier *iden = new Identifier(s);
    assert(log10(iden->toValue()) < maxLen);
    return iden;
}

long Identifier::toValue() {
    long val = stol(this->id);
    return val;
}

string Identifier::hash(string str) {
/*
 * unsigned int i;
    long hash = 0;
    for (i = 0; i < str.length(); i++) {
        hash = hash * 31 + str[i];
    }
    hash = abs(hash);
    return to_string(hash % (long)pow(2, maxLen));
*/
    return str;
}
