#include "queries.h"
#include <chrono>

using namespace std::chrono;

int main () {
    RTree* rtree =  read_neighborhoods("../data/neighborhoods.txt");
    insert_data(rtree, "../data/short_trips.csv");

    auto start = system_clock::now();
    
    query1(rtree);
    //query2(rtree, 5);
    //query3(rtree, Point(-73.922592163085938, 40.754528045654297), Point(-73.91363525390625, 40.765522003173828));
    
    auto end = system_clock::now();
    duration<double> elapsed_seconds = end - start;
    cout << '\n' << "Elapse time: " << elapsed_seconds.count() << ' s\n';
    
    //rtree->print_hojas();
    return 0;
}