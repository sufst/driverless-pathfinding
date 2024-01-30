//
// Created by shree on 26/11/2023.
//

#include <iostream>

#include "Region.h"


Point Region::getBl() const {

    return Point{this->centre.x - this->width/2, this->centre.y + this->height/2};
}

Point Region::getTl() const{
    return Point{this->centre.x - this->width/2, this->centre.y - this->height/2};
}

Point Region::getBr() const{
    return Point{this->centre.x + this->width/2, this->centre.y + this->height/2};
}

Point Region::getTr() const{
    return Point{this->centre.x + this->width/2, this->centre.y - this->height/2};
}

bool Region::isInRange(Point point, double range) {
    if (Point::calcDist(this->getBl(), point) < range || Point::calcDist(this->getTl(), point) < range ||
    Point::calcDist(this->getBr(), point) < range || Point::calcDist(this->getTr(), point) < range) {
        return true;
    }

    if (point.x < this->getBr().x && point.x > this->getBl().x &&
    point.y > this->getTr().y && point.y < this->getBl().y) {
        return true;
    }
    return false;
}


