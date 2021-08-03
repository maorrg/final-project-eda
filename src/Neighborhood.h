#include <iostream>
#include <vector>
#include "Trip.h"
using namespace std;

class Neighborhood{

    public:

    string name;
    vector<Point> coordinates;

    vector<Trip*> pickup;
    int n_pickup;
    vector<Trip*> dropoff;
    int n_dropoff;

    Neighborhood(string name, vector<Point> coordinates){
        this->name = name;
        this->coordinates = coordinates;
        n_pickup = n_dropoff = 0;
        //pickUp = new RangeTree;
        //dropOff = new RangeTree;
    }

    int is_inside(const Point point) {
        vector<Point> polygon = coordinates;
        int intersections = 0;
        double F, dy, dy2 = point.y - polygon[0].y;

        for (int ii = 0, jj = 1; ii < polygon.size(); ++ii, ++jj) {
            dy = dy2;
            dy2 = point.y - polygon[jj].y;

            if (dy * dy2 <= 0. &&
                (point.x >= polygon[ii].x || point.x >= polygon[jj].x)) {

            if ((dy < 0.) || (dy2 < 0.)) {
                F = dy * (polygon[jj].x - polygon[ii].x) / (dy - dy2) + polygon[ii].x;

                if (point.x > F) ++intersections;
                else if (point.x == F) return 1;
                
            } else if (dy2 == 0. && (point.x == polygon[jj].x || (dy == 0. && (point.x - polygon[ii].x) * (point.x - polygon[jj].x) <= 0.))) return 1;
            }
        }
        return intersections & 1;
    }
    
};