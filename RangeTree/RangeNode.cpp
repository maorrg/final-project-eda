#include "RangeNode.h"


bool RangeNode :: isLeaf(){
    return this->left == nullptr && this->right == nullptr;
}

void RangeNode :: killSelf() {

    if (left){
        left->killSelf();
    }
    else if (right){
        right->killSelf();
    }
    delete this;

}