#include "Neighborhood.h"

class MBR {

    public:
    
    Point start;
    Point end;
    Neighborhood* neighborhood;

    MBR(Point start, Point end, Neighborhood* neighborhood) 
    : start(start), end(end), neighborhood(neighborhood){};

    void expand_area(Point start, Point end){  
        auto ppp = calculate_expansion(start, end);
        this->start = ppp.first;
        this->end = ppp.second;
        this->neighborhood = nullptr;
    }
    pair<Point, Point> calculate_expansion(Point start, Point end) {
        auto start_x = min(start.x, this->start.x);
        auto start_y = min(start.y, this->start.y);
        auto end_x = max(end.x, this->end.x);
        auto end_y = max(end.y, this->end.y);
        pair<Point, Point> ppp = {Point(start_x, start_y), Point(end_x, end_y)};
        return ppp;
    }
    double get_area() {
        double hight = end.y - start.y;
        double width = end.x - start.x;
        return hight*width;
    }

};
