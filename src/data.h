#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include "RTree.h"
#include <limits>

const double INF = numeric_limits<double>::max();

using namespace std;

vector<string> split(string s, string delimiter){
    int start = 0;
    int end = s.find(delimiter);
    vector<string> textSplit;
    while (end != -1) {
        textSplit.push_back(s.substr(start, end - start));
        start = end + delimiter.size();
        end = s.find(delimiter, start);
    }
    textSplit.push_back(s.substr(start, end - start));
    return textSplit;
}

void readData(string fileName) {

    ifstream file;
    ofstream ofile ("clean_data.csv");
    file.open(fileName);
    string line, word;
    if (!file.is_open()) return;
    //falta omitir primera linea
    while (getline(file, line)){
        stringstream s(line);
        if (!ofile.is_open()) return;
        vector<string> row = split(line, ",");
        ofile << row[5] << ",";
        ofile << row[6] << ",";
        ofile << row[7] << ",";
        ofile << row[8] << endl;
    }
    //crear objetos trip con {pickup lo row[5]}, {pickup la row[6]}, {drop lo row[7]} y {drop la row[9]}

    /*
    VendorID,lpep_pickup_datetime,Lpep_dropoff_datetime,Store_and_fwd_flag,RateCodeID,Pickup_longitude,Pickup_latitude,Dropoff_longitude,Dropoff_latitude,Passenger_count,Trip_distance,Fare_amount,Extra,MTA_tax,Tip_amount,Tolls_amount,Ehail_fee,improvement_surcharge,Total_amount,Payment_type,Trip_type 
    2,2015-01-01 00:34:42,2015-01-01 00:38:34,N,1,-73.922592163085938,40.754528045654297,-73.91363525390625,40.765522003173828,1,.88,5,0.5,0.5,0,0,,0.3,6.3,2,1,,
    */

    // Close the file
    file.close();

}

RTree* read_neighborhoods(string filename){

    RTree* rtree = new RTree();
    ifstream file;
    string line;
    file.open(filename);
    while (file.is_open()){
        getline(file, line);
        if (line == "-"){
            file.close();
            return rtree;
        }
        vector<Point> points;
        double min_x = INF;
        double min_y = INF;
        double max_x = -INF;
        double max_y = -INF;
        string name = line;
        //cout << line << endl;
        line.clear();
        getline(file, line);
        while(line != "%"){
            if (line != "%"){
            //cout << line << endl;
            vector<string> row = split(line, ",");
            double row_0 = stod(row[0])*1000;
            double row_1 = stod(row[1])*1000;
            points.push_back(Point(row_0,row_1));
            if (row_0 < min_x)
                min_x = row_0;
            else if (row_0 > max_x)
                max_x = row_0;
            if (row_1 < min_y)
                min_y = row_1;
            else if (row_1 > max_y)
                max_y = row_1;
            line.clear();
            getline(file, line);
            }
        }
        Neighborhood* neighborhood = new Neighborhood(name, points);
        rtree->insert(Point(min_x, min_y), Point(max_x, max_y), neighborhood);
    }
    file.close();
    return rtree;
}

void insert_data(RTree*& rtree, string filename) {
    ifstream file;
    file.open(filename);
    string line, word;
    int ID = 0;
    if (!file.is_open()) return;
    getline(file, line);
    while (getline(file, line)){
        stringstream s(line);
        vector<string> row = split(line, ",");
        ID++;
        Point point_pickup (stod(row[0])*1000, stod(row[1])*1000);
        Point point_dropoff (stod(row[2])*1000, stod(row[3])*1000);
        Trip* trip = new Trip(ID, point_pickup, point_dropoff);
        rtree->insert_trip(trip);
    }
    file.close();
}
