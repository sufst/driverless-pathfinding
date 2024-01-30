//
// Created by shree on 27/11/2023.
//

#include "Node.h"
#include "../Config.h"


Node::Node(Point p, double cost, Branch& root) {
    x = p.x;
    y = p.y;
    this->cost = cost;
    root.findClosest(p);
    root.insertPoint(p);
    parent = nullptr;
}

Node& Node::getParent() {
    return *parent;
}

void Node::setParent(Node& par) {
    parent = &par;
}

vector<Node*> Node::getChildren() {
    return children;
}

void Node::addChild(Node& child) {
    children.push_back(&child);
}

void Node::removeChild(Node& child) {
    children.erase(std::remove(children.begin(), children.end(), &child), children.end());
}

void Node::setCost(double c) {
    cost = c;
}

double Node::getCost() {
    return cost;
}

