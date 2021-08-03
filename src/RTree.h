#include "RNode.h"
//#include <omp.h>

enum trip_type{
    type_pickup,
    type_dropoff
};

class RTree{

    private:

    RNode* root;
    RNode* find_subtree(RNode*& node, Point start, Point end, Neighborhood* neighborhood) {
        double right_area = node->right->calculate_expansion_area(start, end);
        double left_area = node->left->calculate_expansion_area(start, end);
        double right_left_area = node->get_area();
        if (right_area <= left_area && right_area <= right_left_area) {
            node->expand_area(start, end);
            return node->right;
        }
        else if (left_area <= right_area && left_area <= right_left_area) {
            node->expand_area(start, end);
            return node->left;
        }
        else {
            RNode* copied_node = new RNode(node);
            RNode* new_parent = new RNode(node);
            new_parent->expand_area(start, end);
            new_parent->left = new RNode(start, end, neighborhood);
            new_parent->right = copied_node;
            *node = new_parent;
            return nullptr;
        }
    }
    void get_neigh(RNode* node, vector<int>& ans) {
        if (node->is_leaf()) {
            auto n = node->MBR->neighborhood;
            search_same_trips(n, ans);
        }
        if (node->right) get_neigh(node->right, ans);
        if (node->left) get_neigh(node->left, ans);
    }
    void print_hojas_recursiva(RNode* node) {
        if (node->is_leaf()) {
            auto n = node->MBR->neighborhood;
            if (n->n_pickup != 0 || n->n_dropoff!=0)
                cout << n->name << endl << "pickup: " << n->n_pickup << ", dropoff: " << n->n_dropoff << endl;
                cout << n->name << endl << "pickup: " << n->n_pickup << ", dropoff: " << n->n_dropoff << endl;
        }
        if (node->right) print_hojas_recursiva(node->right);
        if (node->left) print_hojas_recursiva(node->left);
    }
    void hojas_recursiva(RNode* node, int& n) {
        if (node->is_leaf()) n++;
        if (node->right) hojas_recursiva(node->right, n);
        if (node->left) hojas_recursiva(node->left, n);
    }
    void top_recursive(RNode* node, vector<pair<int, string>>& ans) {
        if (node->is_leaf()) 
            ans.push_back({node->MBR->neighborhood->n_pickup, node->MBR->neighborhood->name});
        if (node->right) top_recursive(node->right, ans);
        if (node->left) top_recursive(node->left, ans);
    }

    public: 

    RTree() {root = nullptr;}

    void insert(Point start, Point end, Neighborhood* neighborhood) {
        if (root == nullptr) {
            root = new RNode(start, end, neighborhood); 
            return;
        }
        RNode* cur = root;
        while (cur != nullptr) {
            if (cur->is_leaf()) {
                cur->split(start, end, neighborhood);
                return;
            }
            cur = find_subtree(cur, start, end, neighborhood);
        }
    }
    void search_recursive(Point point, RNode* node, vector <Neighborhood*>& ans) {
        if (node->match(point)) {
            if (node->is_leaf()) 
                ans.push_back(node->MBR->neighborhood);
            else {
                if (node->right != nullptr) search_recursive(point, node->right, ans);
                if (node->left != nullptr) search_recursive(point, node->left, ans);
            }
        }
    }
    vector <Neighborhood*> search(Point point) {
        vector <Neighborhood*> ans;
        if (root) search_recursive(point, root, ans);
        return ans;
    }
    void insert_trip(Trip* trip) {
        vector <Neighborhood*> pickup_vect = search(trip->pickup);
        for (int i = 0; i < pickup_vect.size(); i++) {
            if (!pickup_vect[i]->is_inside(trip->pickup)) continue;
            //cout << trip->ID << " Pick Up: " << pickup_vect[i]->name << '\n';
            pickup_vect[i]->n_pickup++;
            pickup_vect[i]->pickup.push_back(trip);
            trip->pickup_neighborhoods.push_back(pickup_vect[i]->name);
        }
        vector <Neighborhood*> dropoff_vect = search(trip->dropoff);
        for (int i = 0; i < dropoff_vect.size(); i++) {
            if (!dropoff_vect[i]->is_inside(trip->dropoff)) continue;
            //cout << trip->ID << " Drop Off: " << dropoff_vect[i]->name << '\n';
            dropoff_vect[i]->n_dropoff++;
            dropoff_vect[i]->dropoff.push_back(trip);
            trip->dropoff_neighborhoods.push_back(dropoff_vect[i]->name);
        }
    }

    void same_neighborhood(vector<int>& ans) {
        get_neigh(root, ans);
    }
    void search_same_trips(Neighborhood* neighborhood, vector<int>& ans) {
        for (int i = 0; i < neighborhood->pickup.size(); i++) {
            if (neighborhood->pickup[i]->same()) 
                ans.push_back(neighborhood->pickup[i]->ID);
        }
    }
    void print_hojas() {
        if (root == nullptr) return;
        print_hojas_recursiva(root);
    }
    bool top_pickup(int n, vector<pair<int, string>>& ans) {
        if (root == nullptr) return false;
        top_recursive(root, ans);
        sort(ans.begin(), ans.end());
        ans.erase(ans.begin(), ans.begin()+ans.size()-1-n);
        if (ans.size() < n) return false; 
        return true;
    }

    void search_range_pickup(RNode* node, Point p1, Point p2, int& ans){
        vector<Trip*> vPickup = node->MBR->neighborhood->pickup;
        for (int i=0; i<vPickup.size(); i++){
            if (vPickup[i]->is_in_range(p1,p2)){
                ans++;
            }
        }
    }

    void search_range_neigh_recursive(RNode* node, Point p1, Point p2, int& ans){
        if (node->intersects(p1, p2)) {
            if (node->is_leaf()) search_range_pickup(node, p1, p2, ans);
            else {
                if (node->right != nullptr) search_range_neigh_recursive(node->right, p1, p2, ans);
                if (node->left != nullptr) search_range_neigh_recursive(node->left, p1, p2, ans);
            }
        }
    }

    Point change_units(Point p) {
        return Point(p.x*1000, p.y*1000);
    }

    int search_range_neigh(Point p1, Point p2){
        p1 = change_units(p1);
        p2 = change_units(p2);
        if (root == nullptr) return 0;
        int ans = 0;
        search_range_neigh_recursive(root, p1, p2, ans);
        return ans;
    }

};

