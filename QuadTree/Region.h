//
// Created by shree on 28/09/2023.
//

#ifndef CUSTOMQUADTREE_REGION_H
#define CUSTOMQUADTREE_REGION_H

#include "Point.h"
#include <vector>
using std::vector;

class Region {


protected:
    Region()= default;

    Point getTl() const;
    Point getBl() const;
    Point getTr() const;
    Point getBr() const;

    bool isInRange(Point point,double range);

public:
    bool isLeaf = true;
    Point centre{};
    double height{};
    double width{};

    virtual void insertPoint(const Point& point) = 0;

    virtual Point findClosest(const Point& point) = 0;

    virtual vector<Point> findPointsInRange(const Point& point, double range) = 0;

    virtual vector<Point> getPoints(const Point& point) = 0;

};

#endif //CUSTOMQUADTREE_REGION_H
