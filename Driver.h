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
        double timeAdditions(int n);
        double timeAdditions(int n, int maxN);
        double timeDeletions(int n);
        double timeLookup(int n);


};
