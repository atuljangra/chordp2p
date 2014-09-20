#include "Identifier.h"
#include <math.h>
#include <assert.h>
#include <openssl/sha.h>
#include <iostream>

using namespace std;


bool Identifier::isInBetween(Identifier *a, Identifier *b, int leftClosed, int rightClosed) {
    long valA = a->toValue();
    long valB = b->toValue();
    long maxVal = pow(2.0, maxLen);
    long myVal = this->toValue();
     
    myVal = (myVal <= valA)? (myVal + maxVal) : myVal;
    valB = (valB <= valA)? (valB + maxVal) : valB;
    if (((leftClosed && valA <= myVal) || (!leftClosed && valA < myVal))
            && ((rightClosed && valB >= myVal) || (!rightClosed && valB > myVal)) )
        return true;
    
    /*if (valA > valB)
        valB += maxVal;

    if (((leftClosed && valA <= myVal) || (!leftClosed && valA < myVal))
            && ((rightClosed && valB >= myVal) || (!rightClosed && valB > myVal)) )
        return true;
    */return false;
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
