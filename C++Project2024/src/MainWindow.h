#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class MainWindow {
public:
    MainWindow(int width, int height);
    bool init();
    void run();
    void close();

private:
    int windowWidth, windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool running;
    std::string inputText;

    SDL_Rect buttonRect;
    bool buttonPressed;

    void handleEvents();
    void render();
    void renderText(const std::string& text, int x, int y);
};

#endif // MAINWINDOW_H