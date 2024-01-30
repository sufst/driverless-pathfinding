//
// Created by shree on 29/09/2023.
//

#include <cmath>
#include <queue>
#include "Draw.h"
#include "View.h"
#include "../Graph/Node.h"

void Draw::addPoint(const Point& point) {
    if (!DRAW_QUAD) {
        return;
    }

    SDL_SetRenderDrawColor(View::RENDERER, 255, 255, 255, 255);
    SDL_RenderDrawPoint(View::RENDERER, std::floor(point.x), std::floor(point.y));
}

void Draw::addBigPoint(Point& point) {
    SDL_SetRenderDrawColor(View::RENDERER, 255, 255, 255, 255);
    Point p = Point{std::floor(point.x), std::floor(point.y)};
    addRegion(p, 10, 10);
}

void Draw::addBranch(Point& centre, double width, double height) {
    if (!DRAW_QUAD) {
        return;
    }

    SDL_SetRenderDrawColor(View::RENDERER, 255, 0, 255, 255);
    addRegion(centre, width, height);
}

void Draw::addLeaf(Point& centre, double width, double height) {
    if (!DRAW_QUAD) {
        return;
    }

    SDL_SetRenderDrawColor(View::RENDERER, 0, 255, 255, 255);
    addRegion(centre, width, height);
}

void Draw::addRegion(Point& centre, double width, double height) {
    if (!DRAW_QUAD) {
        return;
    }

    SDL_Rect rect;
    rect.x = std::floor(centre.x - width/2);
    rect.y = std::floor(centre.y - height/2);
    rect.w = std::floor(width);
    rect.h = std::floor(height);
    SDL_RenderDrawRect(View::RENDERER, &rect);
}

void Draw::addRect(int x, int y, int w, int h) {
    SDL_Rect rect {x, y, w, h};

    SDL_SetRenderDrawColor(View::RENDERER, 255, 255, 255, 255);
    SDL_RenderFillRect(View::RENDERER, &rect);
}

void Draw::addLine(Point& start, Point& end) {
    SDL_SetRenderDrawColor(View::RENDERER, 255, 255, 255, 255);

    SDL_RenderDrawLine(View::RENDERER, start.x, start.y, end.x, end.y);
}

void Draw::addColorLine(Point& start, Point& end, int r, int g, int b) {
    SDL_SetRenderDrawColor(View::RENDERER, r, g, b, 255);
    SDL_RenderDrawLine(View::RENDERER, start.x, start.y, end.x, end.y);
}

void Draw::removeLine(Point& start, Point& end) {
    SDL_SetRenderDrawColor(View::RENDERER, 0, 0, 0, 0);

    SDL_RenderDrawLine(View::RENDERER, start.x, start.y, end.x, end.y);
}

void Draw::drawFullGraph(Node& root, Node* endPoint) {
    const auto [r, g, b, a] = View::BACKGROUND_COLOR;

    SDL_SetRenderDrawColor(View::RENDERER, r, g, b, a);
    SDL_RenderClear(View::RENDERER);

    std::queue<Node> queue;
    queue.push(root);

    while (!queue.empty()) {
        Node n = queue.front();

        for (Node* child: n.getChildren()) {
            Draw::addLine(n, *child);
            queue.push(*child);
        }
        queue.pop();
    }

    Node* node = endPoint;

    while (node != nullptr && &node->getParent() != node) {
        Draw::addColorLine(*node,  node->getParent(), 255, 0, 0);
        node = &node->getParent();
    }
}

void Draw::drawObstacles(CordMap &cordMap, vector<std::tuple<int, int, int, int>> &obstacles) {
    SDL_SetRenderDrawColor(View::RENDERER, 100, 100, 100, 255);

    for (std::tuple<int, int, int, int> obstacle: obstacles) {
        SDL_Rect rect{std::get<0>(obstacle), std::get<1>(obstacle), std::get<2>(obstacle), std::get<3>(obstacle)};
        SDL_RenderFillRect(View::RENDERER, &rect);
    }
}
