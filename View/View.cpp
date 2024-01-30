//
// Created by shree on 29/09/2023.
//

#include "View.h"
#include "Draw.h"

SDL_Window* View::window;
View* View::view_;
SDL_Renderer* View::RENDERER = nullptr;

View::View() {
    window = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT, 0, &window, &RENDERER);

    const auto [r, g, b, a] = BACKGROUND_COLOR;

    SDL_SetRenderDrawColor(RENDERER, r, g, b, a);
    SDL_RenderClear(RENDERER);

}

void View::render() {
    SDL_RenderPresent(RENDERER);
}

View *View::getInstance() {
    if (view_ == nullptr) {
        view_ = new View();
    }

    return view_;
}
