#include <iostream>
#include "Point.h"
using namespace std;

class Trip {

    public:

    int ID;
    Point pickup;
    Point dropoff;
    vector<string> pickup_neighborhoods;
    vector<string> dropoff_neighborhoods;

    Trip(int ID, Point pickup, Point dropoff) 
    : ID(ID), pickup(pickup), dropoff(dropoff){}

    bool same(){
        for (auto e1 : pickup_neighborhoods) {
            for (auto e2 : dropoff_neighborhoods) {
                if (e1 == e2) return true;
            }
        }
        return false;
    }
    
    bool is_in_range(Point p1, Point p2){
        return pickup.x >= p1.x && pickup.y >= p1.y && pickup.y <= p2.y && pickup.x <= p2.x;
    }
};