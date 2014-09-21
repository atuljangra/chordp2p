#include <iostream>
#include <string>
#include "Node.h"

extern int maxItems; 
class Driver {
    private:

    public:
        /* 
         * Perform multiple additions and returns the time taken
         */ 
        long long timeAdditions(int n);
        long long timeAdditions(int n, int maxN);
        long long timeDeletions(int n);
        long long timeLookup(int n);
        long long timeEfficacy(int n);
        long long nodeAdditions(int n);

};
