//
// Created by shree on 28/09/2023.
//

#include "Leaf.h"

#include <cmath>
#include "Branch.h"
#include "../Config.h"
#include "../View/Draw.h"
#include "../Logger.h"

void Leaf::convertToBranch() {
    Logger::print(DEBUG, "Turning leaf into a branch", centre, width, height);

    auto newBranch = std::make_shared<Branch>(centre, width, height);
    for (auto& point: points) {
        newBranch->insertPoint(point);
    }

    Logger::print(DEBUG, "Finished turning leaf into a branch");

}

void Leaf::insertPoint(const Point &point) {
    Logger::print(DEBUG, "Inserting point", point);

    points.push_back(point);
    Draw::addPoint(point);


    if (points.size() > MAX_POINTS_LEAF && this->width > 20 && this->height > 20)
        convertToBranch();

    Logger::print(DEBUG, "Inserted point", point);
}

Point Leaf::findClosest(const Point &point) {

    double closestDist = INT_MAX;
    Point closestPoint{};

    for (const Point& pointInTree: points){
        double dist = Point::calcDist(pointInTree, point);

        if (dist < closestDist) {
            closestPoint = pointInTree;
            closestDist = dist;
        }
    }

    return closestPoint;
//    Point closestPoint{};
//    double closest = 99999999999;
//
//    vector<vector<Point>> setOfPoints;
//
//    setOfPoints.push_back(ROOT.getPoints({centre.x + width/2 + 0.1, centre.y}));
//    setOfPoints.push_back(ROOT.getPoints({centre.x - (width/2 + 0.1), centre.y}));
//    setOfPoints.push_back(ROOT.getPoints({centre.x, centre.y + height/2 + 0.1}));
//    setOfPoints.push_back(ROOT.getPoints({centre.x, centre.y - (height/2 + 0.1)}));
//    setOfPoints.push_back(points);
//    for (const vector<Point>& closestPoints: setOfPoints) {
//        Logger::print(closestPoints.size());
//
//        for (Point possibleClosestPoint: closestPoints) {
//            Logger::print(possibleClosestPoint);
//            double dist = pow((possibleClosestPoint.x-point.x),2) + pow((possibleClosestPoint.y-point.y),2);
//            if (dist < closest) {
//                closestPoint = possibleClosestPoint;
//                closest = dist;
//            }
//        }
//    }
//    return closestPoint;
}

vector<Point> Leaf::getPoints(const Point& point) {
    return points;
}

Leaf::Leaf(Point centre, double width, double height) {
    this->centre = centre;
    this->width = width;
    this->height = height;

    Logger::trackMemory(MLeaf, true);

    Draw::addLeaf(centre, width, height);
}

Leaf::Leaf(Point&& centre, double width, double height) {
    this->centre = centre;
    this->width = width;
    this->height = height;

    Logger::trackMemory(MLeaf, true);

    Draw::addLeaf(centre, width, height);
}

Leaf::~Leaf() {
    Logger::trackMemory(MLeaf, false);
}

vector<Point> Leaf::findPointsInRange(const Point& point, double range) {
    std::vector<Point> pointsInRange;

    if (isInRange(point, range)) {
        std::copy_if(points.begin(), points.end(), std::back_inserter(pointsInRange), [point, range](Point p1) {
            return Point::calcDist(p1, point) < range;
        });
    }

    return pointsInRange;
}
