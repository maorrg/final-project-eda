#include "RangeTree.h"
#include <vector>

using namespace std;

RangeNode* RangeTree :: find_by_key(int key){
    if (!root) return nullptr;
    Node** node = &this->root;
    while(*node){
        if((*node)->key == key && (*node)->isLeaf())
            return *node;
        else
            node = (key > (*node)->key) ? &(*node)->right : &(*node)->left;
    }
    return nullptr;
}

int RangeTree :: setHeight(Node* &root_){
    if(!root_)
        return 0;
    else{
        int height_left = setHeight(root_->left);
        int height_right = setHeight(root_->right);
        return 1 + std::max(height_left,height_right);
    }
}

int RangeTree :: balanceFactor(Node* &root_){
    if(!root_) return 0;
    else {
        int height_left = setHeight(root_->left);
        int height_right = setHeight(root_->right);
        return height_right - height_left;
    }
}

void RangeTree :: rightR (Node* &node){
    auto parent = node->left;
    auto left = parent->right;

    parent->right = node;
    node->left = left;

    node->height = setHeight(node);
    parent->height = setHeight(parent);

    if(node == this->root)
        this->root = parent;

    node = parent;
}

void RangeTree :: leftR (Node* &node){

    auto parent = node->right;
    auto right = parent->left;

    parent->left = node;
    node->right = right;

    node->height = setHeight(node);
    parent->height = setHeight(parent);

    if(node == this->root)
        this->root = parent;

    node = parent;
}

RangeNode* RangeTree :: insert_(Node* &node, int key, int x, int y, Node* &toInsert){

    if (!node) {
        node = new Node(key, x, y);
        this->nodes++;
        return node;
    }
    if (key < node->key) {
        if (!node->left)
            toInsert = new Node (key, x, y);
        node->left = insert_(node->left, key, x, y, toInsert);
    }
    else if (key >= node->key) {
        if (!node->right)
            toInsert = new Node (node->key, node->x, node->y);
        node->right = insert_(node->right, key, x, y, toInsert);
    }
    else return node;

    node->height = setHeight(node);

    if (nodes > 2 && nodes % 2 == 1) {

        int balf = balanceFactor(node);

        if(balf > 1 && key < node->right->key) {
            rightR(node->right);
            leftR(node);
        }

        else if(balf < -1 && key >= node->left->key) {
            leftR(node->left);
            rightR(node);
        }

        else if(balf > 1 && key >= node->right->key)
            leftR(node);

        else if(balf < -1 && key < node->left->key)
            rightR(node);
    }

    return node;
}

bool RangeTree :: insertKey(int key, int x, int y){
    if(x < 0 or y < 0)
        throw out_of_range ("Index invalido");
    else{
        Node* toInsert = nullptr;
        insert_(this->root, key, x, y,toInsert);
        if (nodes > 1)
            insert_(this->root, toInsert->key, toInsert->x, toInsert->y, toInsert);
        return true;
    }
}

bool RangeTree :: insert(int x, int y, Trip* trip){
    //buscar antes de agregar, si existe meter en vector de trip
    return insertKey(x, x, y);
}

void RangeTree :: split(Node** &node, int x1, int x2){
    node = &this->root;
    while(*node) {
        if (x1 > ((*node)->key) && x2 > ((*node)->key))
            node = &(*node)->right;
        else if (x1 <= ((*node)->key) && x2 <= ((*node)->key))
            node = &(*node)->left;
        else break;
    }
}

void RangeTree :: searchRange(Node* &node, int x1, int x2, vector<Node*> &vector) {
    if(node) {
        if (!node->left && !node->right && node->key >= x1 && node->key <= x2)
            vector.push_back(node);
        else {
            if (node->key < x1)
                searchRange(node->right, x1, x2, vector);
            else if (node->key >= x2)
                searchRange(node->left, x1, x2, vector);
            else if (node->key >= x1 && node->key < x2) {
                searchRange(node->left, x1, x2, vector);
                searchRange(node->right, x1, x2, vector);
            }
        }
    }
}