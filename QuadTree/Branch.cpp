//
// Created by shree on 28/09/2023.
//
#include <iostream>
#include "Branch.h"
#include "Leaf.h"
#include <cmath>
#include "../View/Draw.h"
#include "../Logger.h"

std::shared_ptr<Region> Branch::getQuadrant(const Point &point) {
    if (point.x < centre.x) {
        if (point.y > centre.y) {
            return quadrantDirections.bl;
        } else {
            return quadrantDirections.tl;
        }
    }else {
        if (point.y > centre.y) {
            return quadrantDirections.br;
        } else {
            return quadrantDirections.tr;
        }
    }
}

void Branch::insertPoint(const Point &point) {
    getQuadrant(point)->insertPoint(point);
}

Point updateClosest(Point closestPoint, Point closestPointContender, Point point) {
    if (Point::calcDist(closestPoint, point) < Point::calcDist(closestPointContender, point)) {
        return closestPoint;
    } else {
        return closestPointContender;
    }
}

Point Branch::findClosest(const Point &point) {
    Point closestPoint = getQuadrant(point)->findClosest(point);

    if (closestPoint.isNull()){
        closestPoint = updateClosest(closestPoint, quadrantDirections.br->findClosest(point), point);
        closestPoint = updateClosest(closestPoint, quadrantDirections.tl->findClosest(point), point);
        closestPoint = updateClosest(closestPoint, quadrantDirections.tr->findClosest(point), point);
        closestPoint = updateClosest(closestPoint, quadrantDirections.bl->findClosest(point), point);
    } else {
        double closestDist = Point::calcDist(closestPoint, point);;
        if (getQuadrant(point) == quadrantDirections.br) {
            if (closestDist > fabs(point.x - centre.x)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.bl->findClosest(point), point);
            }
            if (closestDist > fabs(centre.y - point.y)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.tr->findClosest(point), point);
            }
        } else if (getQuadrant(point) == quadrantDirections.tr) {
            if (closestDist > fabs(point.x - centre.x)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.bl->findClosest(point), point);
            }
            if (closestDist > fabs(point.y - centre.y)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.bl->findClosest(point), point);
            }
        } else if (getQuadrant(point) == quadrantDirections.tl) {
            if (closestDist > fabs(centre.x - point.x)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.tr->findClosest(point), point);
            }
            if (closestDist > fabs(point.y - centre.y)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.bl->findClosest(point), point);
            }
        }else if (getQuadrant(point) == quadrantDirections.bl) {
            if (closestDist > fabs(centre.x - point.x)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.br->findClosest(point), point);
            }
            if (closestDist > fabs(centre.y - point.y)) {
                closestPoint = updateClosest(closestPoint, quadrantDirections.tl->findClosest(point), point);
            }
        }
    }

    return closestPoint;
}

vector<Point> Branch::findPointsInRange(const Point &point, double range) {

    vector<Point> pointsInRange;
    if (isInRange(point, range)) {
        vector<Point> temp = quadrantDirections.tl->findPointsInRange(point, range);
        pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
        temp = quadrantDirections.tr->findPointsInRange(point, range);
        pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
        temp = quadrantDirections.bl->findPointsInRange(point, range);
        pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
        temp = quadrantDirections.br->findPointsInRange(point, range);
        pointsInRange.insert(pointsInRange.end(), temp.begin(), temp.end());
    }
    return pointsInRange;
}

vector<Point> Branch::getPoints(const Point &point) {
    auto points = getQuadrant(point)->getPoints(point);
    if (points.empty()) {
        vector<Point> newVector;
        vector<Point> temp = quadrantDirections.tl->getPoints(point);
        newVector.insert(newVector.end(), temp.begin(), temp.end());
        temp = quadrantDirections.br->getPoints(point);
        newVector.insert(newVector.end(), temp.begin(), temp.end());
        temp = quadrantDirections.tr->getPoints(point);
        newVector.insert(newVector.end(), temp.begin(), temp.end());
        temp = quadrantDirections.bl->getPoints(point);
        newVector.insert(newVector.end(), temp.begin(), temp.end());
        return std::move(newVector);
    }

    return std::move(points);
}

Branch::Branch(Point centre, double width, double height) {
    this->centre = centre;
    this->width = width;
    this->height = height;
    isLeaf = false;

    Logger::trackMemory(MBranch, true);

    Draw::addBranch(centre, width, height);

    Point temp {centre.x - width/4, centre.y - height/4};
    quadrantDirections.tl = std::make_shared<Leaf>(temp, width/2, height/2);
    temp = {centre.x + width/4, centre.y - height/4};
    quadrantDirections.tr = std::make_shared<Leaf>(temp, width/2, height/2);
    temp = {centre.x - width/4, centre.y + height/4};
    quadrantDirections.bl = std::make_shared<Leaf>(temp, width/2, height/2);
    temp = {centre.x + width/4, centre.y + height/4};
    quadrantDirections.br = std::make_shared<Leaf>(temp, width/2, height/2);
}

Branch::~Branch() {
    Logger::trackMemory(MBranch, false);
}