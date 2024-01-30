//
// Created by shree on 27/11/2023.
//

#include "CordMap.h"

void CordMap::addToSet(int x, int y) {
    unavailable.insert((x << 16) + y);
}

bool CordMap::isAvailable(Point point) {
    return !unavailable.contains(((int)point.x << 16) + (int)point.y);
}
