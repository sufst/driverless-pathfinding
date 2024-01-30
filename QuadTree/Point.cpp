//
// Created by shree on 29/09/2023.
//

#include "Point.h"
#include "cmath"

std::ostream &operator<<(std::ostream& os, const Point& point) {
    return os << "(" << point.x << "," << point.y << ")";
}

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

Point operator+(const Point& lhs, const Point& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

bool Point::isNull() const {
    if (x == -999 && y == -999) {
        return true;
    }

    return false;
}

double Point::calcDist(const Point& point1,const Point& point2){
    return sqrt(pow((point1.x-point2.x),2) + pow((point1.y-point2.y),2));
}