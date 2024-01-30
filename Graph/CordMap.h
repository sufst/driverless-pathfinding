//
// Created by shree on 27/11/2023.
//

#ifndef CUSTOMQUADTREE_CORDMAP_H
#define CUSTOMQUADTREE_CORDMAP_H

#include <unordered_set>
#include "../QuadTree/Point.h"

using std::unordered_set;

class CordMap {

private:
    unordered_set<unsigned long> unavailable;

public:
    void addToSet(int x, int y);

    bool isAvailable(Point point);
};


#endif //CUSTOMQUADTREE_CORDMAP_H
