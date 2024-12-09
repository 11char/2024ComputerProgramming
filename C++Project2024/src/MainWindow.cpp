#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(int width, int height)
        : windowWidth(width), windowHeight(height), running(true), inputText("Beat Guesser"),
          window(nullptr), renderer(nullptr), font(nullptr), buttonPressed(false) {
    buttonRect = {100, 200, 200, 50};
}

bool MainWindow::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL2 Input and Button", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("../font/arial.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void MainWindow::run() {
    while (running) {
        handleEvents();
        render();
    }
}

void MainWindow::close() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void MainWindow::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN) {
            if (e.type == SDL_TEXTINPUT) {
                inputText += e.text.text;
            } else if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                inputText.pop_back();
            }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
                y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                buttonPressed = true;
                std::cout << "Button pressed! Input: " << inputText << std::endl;
            }
        }
    }
}

void MainWindow::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render text input
    renderText(inputText, 50, 50);

    // Render button
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &buttonRect);

    renderText("Submit", buttonRect.x + 50, buttonRect.y + 10);

    SDL_RenderPresent(renderer);
}

void MainWindow::renderText(const std::string& text, int x, int y) {
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Unable to create texture from text surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}