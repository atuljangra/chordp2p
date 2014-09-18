#include "Identifier.h"
#include <math.h>
#include <assert.h>

using namespace std;

// Closed interval at larger one.
bool Identifier::isInBetween(Identifier a, Identifier b) {
    long long valA = a.toValue();
    long long valB = b.toValue();

    long long larger = (valA > valB) ? valA : valB;
    long long smaller = (valA < valB) ? valA : valB;

    long long val = this->toValue();
    return (val > smaller) && (val <= larger); 
}

Identifier * Identifier::toIdentifier(string s) {
    Identifier *iden = new Identifier(s);
    assert(log10(iden->toValue()) < maxLen);
    return iden;
}

long long Identifier::toValue() {
    long long val = stoll(this->id);
    return val;
}

//TODO Implement this.
string Identifier::hash(string s) {

    return s;
}
