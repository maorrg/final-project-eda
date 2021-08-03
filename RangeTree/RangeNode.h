#include <iostream>
#include "Trip.h"
using namespace std;

class RangeNode {

public:
    int key;
    int x;
    int y;
    int height;
    RangeNode* left;
    RangeNode* right;
    
    //cambiar a vector
    vector<Trip*> trip;

    RangeNode(int key, int x, int y): height(1), key(key){
        left = nullptr;
        right = nullptr;
        this->x = x;
        this->y = y;
    }

    bool isLeaf();
    void killSelf();

    friend class RangeTree;
};