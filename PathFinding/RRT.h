//
// Created by shree on 27/11/2023.
//

#ifndef CUSTOMQUADTREE_RRT_H
#define CUSTOMQUADTREE_RRT_H


#include <unordered_map>
#include <unordered_set>
#include "../QuadTree/Point.h"
#include "../Graph/Node.h"
#include "../QuadTree/Branch.h"
#include "../Graph/CordMap.h"

class RRT {
private:
    Node* startNode;
    Node* endNode = nullptr;
    Point endPoint;
    Branch& root;
    CordMap cordMap;

    std::unordered_map<unsigned long, Node*> cordToNode;

    Node* pointToNodeConverter(Point p);

    void addNodeToMap(Node& n);

    Point getRandomPoint();

    Node* getClosestNode(Point point);

    vector<Node*> getNodesInRegion(const Point& point, double range);

    static void addEdge(Node& parent, Node& child);

    static void removeEdge(Node& parent, Node& child);

    bool isIntersecting(const Point& s, const Point& e);

    void updateNeighbours(Node& node);

    void updateWeights(Node &node);

    void pathToRoot(Node *node);

public:
    double range;

    double lineDist;

    RRT() = delete;

    RRT(Point start, Point end, double range, double lineDist, Branch& root, CordMap& cordMap);

    void oneStep();

    Node& getStartNode();
    Node* getEndNode();
};


#endif //CUSTOMQUADTREE_RRT_H
