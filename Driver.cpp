#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <cassert>
#include "Driver.h"

using namespace std;

unordered_map<int, bool> map;

int getUniqueKey(bool);

void initMap(long no) {
    for (long i = 0; i < no; i++) 
        map[i] = false;
}

double Driver::timeAdditions(int number) {
    
    return timeAdditions(number, (int)ceil(log2(number)));
}

double Driver::timeAdditions(int number, int maxN) {
    // MaxLen would be equal to ceiling of log(number);
    maxLen = maxN;
    long maxNodes = pow(2.0, maxLen);
    cout << "MAXLEN is " << maxLen << endl;
    Node *nodes[maxNodes-1];
    initMap(maxNodes);
    
    map[0] = true;
    // starting node
    nodes[0] = new Node(0);
    nodes[0] -> start();
    nodes[0] -> join(NULL);
    
    //  Creating the nodes.
    for (int i = 0; i < number - 1; i++) {
        int join = getUniqueKey(true);
        int id = getUniqueKey(false);
        nodes[id] = new Node(id);
        nodes[id] -> start();
        nodes[id] -> join(nodes[join]);
//        cout << "-------------------------------------"<< endl;
    }

   
    Node::resetMessageCount();
    // Start clock.
    clock_t start = clock(); 
    for (int i = 0; i < maxNodes - 1; i++) {
        nodes[getUniqueKey(true)]->addValueForKey(to_string(i), to_string(i + maxNodes));
    }
    clock_t end = clock();
    long count = Node::getMessageCount();
    for (int i = 0; i < maxNodes; i++) {
        if (map[i] == true) {
   //         nodes[i]->printKeysAndFingers();
        }
    }
    
    clock_t timeTaken = (end - start) / (double)(CLOCKS_PER_SEC / 1000);
    cout << "Time taken for " << maxNodes << " msgs on " << number << 
        " Nodes is " << timeTaken << "ms!" << endl;
    cout << "Messages passed " << count << endl;
    map.erase(map.begin(), map.end());
    return timeTaken;
}


int getUniqueKey(bool exist) {
    long maxNodes = pow(2.0, maxLen);
    int start = rand() % maxNodes;
    for (int i = start; i < maxNodes; i++) {
        if (map[i] == exist) {
            map[i] = true;
            return i;
        }
    }

    for (int i = 0; i < maxNodes; i++) {
        if (map[i] == exist) {
            map[i] = true;
            return i;
        }
    }
    cout << " No free id's available" << endl;
    assert(0);
}


