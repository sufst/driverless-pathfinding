//
// Created by shree on 29/09/2023.
//

#ifndef CUSTOMQUADTREE_DRAW_H
#define CUSTOMQUADTREE_DRAW_H


#include <SDL2/SDL_pixels.h>
#include "../QuadTree/Point.h"
#include "../Graph/Node.h"
#include "../Graph/CordMap.h"

class Draw {
private:
    static const bool DRAW_QUAD = false;
    static void addRegion(Point& centre, double width, double height);

public:
    static void addPoint(const Point& point);
    static void addBranch(Point& centre, double width, double height);
    static void addLeaf(Point& centre, double width, double height);
    static void addRect(int x, int y, int w, int h);
    static void addBigPoint(Point& point);
    static void addLine(Point& start, Point& end);
    static void addColorLine(Point& start, Point& end, int r, int g, int b);
    static void removeLine(Point& start, Point& end);
    static void drawFullGraph(Node &root, Node* endPoint);
    static void drawObstacles(CordMap& cordMap, vector<std::tuple<int, int, int, int>>& obstacles);
};


#endif //CUSTOMQUADTREE_DRAW_H
