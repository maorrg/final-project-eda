#include "MBR.h"
#include <vector>

#include <iostream>
using namespace std;

class RNode {

    public:

    MBR* MBR;
    RNode* right;
    RNode* left;

    RNode(Point start, Point end, Neighborhood* neighborhood) { 
        right = nullptr;
        left = nullptr;
        MBR = new class MBR(start, end, neighborhood); 
    }

    RNode(RNode* node) {
        right = node->right;
        left = node->left;
        MBR = new class MBR(node->MBR->start, node->MBR->end, node->MBR->neighborhood); 
    }
    bool is_leaf(){
        return right == nullptr && left == nullptr;
    }
    double get_area() {
        return MBR->get_area();
    }
    double calculate_expansion_area(Point start, Point end) {
        auto ppp = MBR->calculate_expansion(start, end);
        auto hight = ppp.second.y - ppp.first.y;
        auto width = ppp.second.x - ppp.first.x;
        return hight*width;
    }
    void expand_area(Point start, Point end) {
        MBR->expand_area(start, end);
    }
    void split(Point start, Point end, Neighborhood*  neighborhood) { 
        right = new RNode(MBR->start, MBR->end, MBR->neighborhood); 
        left = new RNode(start, end, neighborhood); 
        expand_area(start, end);
    }
    bool match(Point point) {
        bool check_x = point.x >= MBR->start.x && point.x <= MBR->end.x;
        bool check_y = point.y >= MBR->start.y && point.y <= MBR->end.y;
        return check_x && check_y;
    }

    bool intersects(Point p1, Point p2) {
        //return p1.x >= MBR->start.x && p1.y >= MBR->start.y && p2.x <= MBR->end.x && p2.y <= MBR->end.y;
        if (p2.x < MBR->start.x || p1.x > MBR->end.x) {//a la izquierda, a la derecha
            return false; 
        }
        if (p1.y > MBR->end.y || p2.y < MBR->start.y) {//arriba, abajo
            return false; 
        }
        return true;
    }

};
