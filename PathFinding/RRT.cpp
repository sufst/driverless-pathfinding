//
// Created by shree on 27/11/2023.
//

#include <queue>
#include "RRT.h"
#include "../Config.h"

RRT::RRT(Point start, Point end, double range, double lineDist, Branch& root, CordMap& cordMap): root(root) {
    endPoint = end;

//    this->root = root;

    startNode = new Node(start, 0, root);
    startNode->setParent(*startNode);
    addNodeToMap(*startNode);

    this->range = range;
    this->lineDist = lineDist;

    this->cordMap = cordMap;
}


void RRT::addNodeToMap(Node& n){
    cordToNode[((int)n.x << 16 )+ (int)n.y] = &n;
    return;
}

Node* RRT::pointToNodeConverter(Point p) {
    return cordToNode[((int)p.x << 16) + (int)p.y];
}

Point RRT::getRandomPoint() {
    return Point{1.0 * getRandomNumber(0,SPACE_WIDTH), 1.0 * getRandomNumber(0,SPACE_HEIGHT)};
}

Node* RRT::getClosestNode(Point point) {
    Point p = root.findClosest(point);
    return pointToNodeConverter(p);
}

vector<Node *> RRT::getNodesInRegion(const Point& point, double range) {
    vector<Point> ps = root.findPointsInRange(point, range);

    vector<Node*> nodes;

    for (Point p: ps){
        Node* n = pointToNodeConverter(p);
        if (n != nullptr) {
            nodes.push_back(n);
        }
    }

    return nodes;
}

void RRT::addEdge(Node& parent, Node& child) {
    parent.addChild(child);
    child.setParent(parent);
}

void RRT::removeEdge(Node& parent, Node& child) {
    parent.removeChild(child);
}

Point scaleLine(const Point& s, const Point& e, double lineDist) {
    double alpha = lineDist / Point::calcDist(s, e);

    return Point{s.x + (e.x - s.x) * alpha,s.y + (e.y - s.y) * alpha};
}

bool RRT::isIntersecting(const Point& s, const Point& e) {
    for (double sc = 0.0; sc < 1; sc+=0.1) {
        if (!cordMap.isAvailable(scaleLine(s, e, sc))) {
            return true;
        }
    }
    return false;
}

void RRT::updateWeights(Node& node) {
    std::queue<Node*> queue;
    queue.push(&node);

    while (!queue.empty()) {
        Node* n = queue.front();

        n->setCost(n->getParent().getCost() + Point::calcDist(n->getParent(), *n));
        for (Node* child: n->getChildren()) {
            queue.push(child);
        }
        queue.pop();
    }
}

void RRT::updateNeighbours(Node& node) {
    vector<Node*> neighbours = getNodesInRegion(node, range);
    for (Node* neighbour: neighbours) {
        if (node.getCost() + Point::calcDist(node, *neighbour) < neighbour->getCost()) {

            removeEdge(neighbour->getParent(), *neighbour);
            neighbour->setParent(node);
            node.addChild(*neighbour);
            updateWeights(*neighbour);

            updateNeighbours(*neighbour);
        }
    }
}

void RRT::oneStep() {
    Point p = getRandomPoint();

//    Node closestPoint = getClosestNode(p);
    Node* temp = getClosestNode(p);
    Node* closestPoint = temp;

    // Get node with the cost in the area.
    vector<Node*> nodes = getNodesInRegion(*closestPoint, range);
    for (Node* node: nodes) {
        if (node->getCost() + Point::calcDist(*node, p) < closestPoint->getCost()) {
            closestPoint = node;
        }
    }

    Point scaledPoint = scaleLine(*closestPoint, p, lineDist);

    if (isIntersecting(*closestPoint, scaledPoint)) {
        return;
    }

    Node* newNode = new Node{scaledPoint, closestPoint->getCost() + Point::calcDist(*closestPoint, scaledPoint), root};

    addNodeToMap(*newNode);

    addEdge(*closestPoint, *newNode);

    updateNeighbours(*newNode);

}

Node &RRT::getStartNode() {
    return *startNode;
}

Node *RRT::getEndNode() {
    Node& n = *getClosestNode(endPoint);

    if (Point::calcDist(n, endPoint) < 50) {
        endNode = &n;
    }
    return endNode;
}


