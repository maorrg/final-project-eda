#include "queries.h"

int main () {
    RTree* rtree =  read_neighborhoods("../data/neighborhoods.txt");
    insert_data(rtree, "../data/short_trips.csv");
    //insert_data(rtree, "../data/test.txt");
    //query1(rtree);
    //free(rtree);
    //query2(rtree, 5);

    //rtree->print_hojas();
    query3(rtree, Point(-73.922592163085938, 40.754528045654297), Point(-73.91363525390625, 40.765522003173828));
    return 0;
}