//
// Created by shree on 28/09/2023.
//
#ifndef CUSTOMQUADTREE_POINT_H
#define CUSTOMQUADTREE_POINT_H

#include <ostream>

struct Point{
    double x;
    double y;

    Point() {
        x = -999;
        y = -999;
    }

    Point (double x, double y) {
        this->x = x;
        this->y = y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point& point);

    friend bool operator==(const Point& lhs, const Point& rhs);

    friend Point operator+(const Point& lhs, const Point& rhs);

public:
    bool isNull() const;

    static double calcDist(const Point& point1, const Point& point2);
};

#endif //CUSTOMQUADTREE_POINT_H
