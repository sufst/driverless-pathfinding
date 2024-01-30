//
// Created by shree on 28/09/2023.
//

#ifndef CUSTOMQUADTREE_LEAF_H
#define CUSTOMQUADTREE_LEAF_H

#include "Region.h"
#include <vector>
#include <set>
#include <memory>

using std::vector;
using std::set;

class Leaf: public Region {
private:
    vector<Point> points;
    void convertToBranch();

public:
    Leaf(Point&& centre, double width, double height);

    Leaf(Point centre, double width, double height);

    ~Leaf();

    void insertPoint(const Point &point) override;

    Point findClosest(const Point& point) override;

    vector<struct Point> getPoints(const Point& point) override;

    vector<Point> findPointsInRange(const Point& point, double range) override;
};

#endif //CUSTOMQUADTREE_LEAF_H