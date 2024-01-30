//
// Created by shree on 27/11/2023.
//

#ifndef CUSTOMQUADTREE_NODE_H
#define CUSTOMQUADTREE_NODE_H


#include "../QuadTree/Point.h"
#include "../QuadTree/Branch.h"
#include <vector>
#include <iostream>

using std::vector;

class Node: public Point {
private:
    Node* parent;
    vector<Node*> children;
    double cost;

public:
    Node (Point p, double cost, Branch& root);

    Node& getParent();

    void setParent(Node&);

    vector<Node*> getChildren();

    void addChild(Node& n);

    void removeChild(Node& n);

    void setCost(double cost);

    double getCost();
};


#endif //CUSTOMQUADTREE_NODE_H
