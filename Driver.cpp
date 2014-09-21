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

long long Driver::timeAdditions(int number) {
    
    return timeAdditions(number, (int)ceil(log2(number)));
}

long long Driver::timeEfficacy(int number) {
    // MaxLen would be equal to ceiling of log(number);
    maxLen = (int)ceil(log2(number));
    long maxNodes = pow(2.0, maxLen);
   // cout << "MAXLEN is " << maxLen << endl;
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
    }

   
    Node::resetEfficacy();
    // Start clock.
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < maxNodes - 1; i++) {
        nodes[getUniqueKey(true)]->addValueForKey(to_string(i), to_string(i + maxNodes));
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    long count = Node::getEfficacy();
    
    Node::resetEfficacy(); 
    // long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // cout << "Time taken for " << maxNodes << " msgs on " << number << 
       // " Nodes is " << microseconds << "ms!" << endl;
    // cout << "Messages passed " << count << endl;
    map.erase(map.begin(), map.end());
    return count;
}

long long Driver::timeAdditions(int number, int maxN) {
    // MaxLen would be equal to ceiling of log(number);
    maxLen = maxN;
    long maxNodes = pow(2.0, maxLen);
   // cout << "MAXLEN is " << maxLen << endl;
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
    }

   
    Node::resetMessageCount();
    // Start clock.
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < maxNodes - 1; i++) {
        nodes[getUniqueKey(true)]->addValueForKey(to_string(i), to_string(i + maxNodes));
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    long count = Node::getMessageCount();
    for (int i = 0; i < maxNodes; i++) {
        if (map[i] == true) {
        }
    }
    
    count = count/number;
    // long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // cout << "Time taken for " << maxNodes << " msgs on " << number << 
       // " Nodes is " << microseconds << "ms!" << endl;
    // cout << "Messages passed " << count << endl;
    map.erase(map.begin(), map.end());
    Node::resetMessageCount();
    return count;
}

long long Driver::nodeAdditions(int number) {
    // MaxLen would be equal to ceiling of log(number);
    maxLen = (int)ceil(log2(number));
    long maxNodes = pow(2.0, maxLen);
  //  cout << "MAXLEN is " << maxLen << endl;
    Node *nodes[maxNodes-1];
    initMap(maxNodes);
    Node::resetMessageCount(); 
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

    long count = Node::getMessageCount();
    count = count/number;
    Node::resetMessageCount();
  //  cout << "Messages passed " << count << endl;
    map.erase(map.begin(), map.end());
    return count;
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


