//
// Created by shree on 28/09/2023.
//

#ifndef CUSTOMQUADTREE_BRANCH_H
#define CUSTOMQUADTREE_BRANCH_H

#include "Region.h"
#include <memory>


struct QuadrantDirections{
    std::shared_ptr<Region> tl;
    std::shared_ptr<Region> bl;
    std::shared_ptr<Region> tr;
    std::shared_ptr<Region> br;
};

class Branch: public Region {
private:
    QuadrantDirections quadrantDirections;

    std::shared_ptr<Region> getQuadrant(const Point &point);

public:
    Branch(Point centre, double width, double height);

    ~Branch();

    void insertPoint(const Point &point) override;

    Point findClosest(const Point& point) override;

    vector<Point> getPoints(const Point& point) override;

    vector<Point> findPointsInRange(const Point &point, double range) override;
};


#endif //CUSTOMQUADTREE_BRANCH_H
