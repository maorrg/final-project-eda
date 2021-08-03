
#include "RangeNode.h"
#include <vector>
using namespace std;

class RangeTree {

typedef RangeNode Node;

public:

    Node *root;
    int nodes;

private:

    int setHeight(Node* &root_);
    Node* find_by_key(int key);
    int balanceFactor(Node* &root_);
    void rightR (Node* &node);
    void leftR (Node* &node);
    Node* insert_(Node* &node, int key, int x, int y, Node* &toInsert);
    bool insertKey(int key, int x, int y);

public:

    RangeTree() : root(nullptr), nodes(0){};

    //agregar en el Tree en el nodo HOJA que agregue (cajita)
    bool insert(int x, int y, Trip* trip);
    void split(Node** &node, int x1, int x2);
    vector<Node*> search(Point p1, Point p2);
    void searchRange(Node* &node, int x1, int x2, vector<Node*> &list);

};
