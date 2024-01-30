#include <iostream>
#include "QuadTree/Branch.h"
#include "View/View.h"
#include "Logger.h"
#include "Test/ClosestPointTest.h"
#include "View/Draw.h"
#include "PathFinding/RRT.h"


void addObstacles(CordMap& cordMap, const vector<std::tuple<int, int, int, int>>& obstacles) {
    for (std::tuple<int, int, int, int> obstacle: obstacles) {
        for (int i = 0; i < std::get<2>(obstacle); i++) {
            for (int j = 0; j < std::get<3>(obstacle); j++) {
                cordMap.addToSet(std::get<0>(obstacle)+i, std::get<1>(obstacle)+j);
            }
        }
    }
}

void rrtDemo(Branch branch) {
    CordMap cordMap = *new CordMap;
    vector<std::tuple<int, int, int, int>> obstacles;

    obstacles.emplace_back(400, 400, 100, 20);
    obstacles.emplace_back(250, 250, 150, 150);
    obstacles.emplace_back(100, 100, 50, 50);

    addObstacles(cordMap, obstacles);

    Point start = Point{450, 450};
    Point end = Point{450, 150};

    double range = 20;
    double edgeLength = 5;
    RRT* rrt = new RRT(start, end, range, edgeLength, branch, cordMap);

    for (int i = 0; i < 4000; i++) {
        rrt->oneStep();

        if (i % 1 == 0) {
            Draw::drawFullGraph(rrt->getStartNode(), rrt->getEndNode());
            Draw::drawObstacles(cordMap, obstacles);
            View::render();
//            range -= 0.001;
            edgeLength -= 0.05;
        }
        View::render();
    }
}

void quadTreeDemo(Branch branch) {
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    Point point{1.0 * mouseX, 1.0 * mouseY};
                    branch.insertPoint(point);

                    std::cout << "Inserting point: " << point << std::endl;

                } else if (event.button.button == SDL_BUTTON_RIGHT) {

                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    vector<Point> pointsInRange = branch.findPointsInRange({1.0 * mouseX, 1.0 * mouseY}, 100);

                    for (Point point: pointsInRange) {
                        Draw::addBigPoint(point);
                    }
                    std::cout << "Got points in range" << std::endl;
                }
            }
        }
        View::render();
    }
}


int main(int argc, char* args[]) {
    std::cout << "Hello, World!" << std::endl;
    View::getInstance(); // instantiate view

    Branch branch = *new Branch({SPACE_WIDTH/2,SPACE_HEIGHT/2}, SPACE_WIDTH, SPACE_HEIGHT);

    rrtDemo(branch);
//    quadTreeDemo(branch);
    return 0;
}