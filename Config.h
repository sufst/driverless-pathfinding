//
// Created by shree on 29/09/2023.
//

#ifndef CUSTOMQUADTREE_CONFIG_H
#define CUSTOMQUADTREE_CONFIG_H

#include <random>
#include "QuadTree/Branch.h"

static const int MAX_POINTS_LEAF = 50;
static const int SPACE_WIDTH = 500;
static const int SPACE_HEIGHT = 500;


static const int getRandomNumber(int min, int max) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(gen);
}

#endif //CUSTOMQUADTREE_CONFIG_H
