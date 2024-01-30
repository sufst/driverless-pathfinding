//
// Created by shree on 29/09/2023.
//

#ifndef CUSTOMQUADTREE_VIEW_H
#define CUSTOMQUADTREE_VIEW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <tuple>
#include "../Config.h"

class View {
private:
    static SDL_Window* window;
    static const int WINDOW_WIDTH = SPACE_WIDTH;
    static const int WINDOW_HEIGHT = SPACE_HEIGHT;
    static View* view_;


protected:
    View();

public:
    View(View &other) = delete;
    void operator=(const View&) = delete;
    static SDL_Renderer* RENDERER;

    static void render();

    static View *getInstance();

    static constexpr std::tuple<int, int, int, int> BACKGROUND_COLOR = {0,0,0,255};
};

#endif //CUSTOMQUADTREE_VIEW_H
