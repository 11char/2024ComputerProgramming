#include "GameController.h"
#include <iostream>
#include "MainWindow.h"
#define BPM 120
#define SEQUENCE_LENGTH 4

int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    try {

        GameController gameController(SEQUENCE_LENGTH, BPM);
        while(true)
        {
            gameController.playSequence();
            char repeat = false;
            std::cout << "Listen again? (y/n)" << std::endl;
            std::cin >> repeat;
            if(repeat =='n')
            {
                break;
            }

        }
        gameController.printSequence();
        std::vector<int> user_sequence;
        while(true)
        {
            int userInt = 0;
            std::cout << "answer" << std::endl;
            std::cin >> userInt;
            if(userInt >= 0)
            {
                user_sequence.push_back(userInt);
            }
            else
            {
                break;
            }
        }
        if(gameController.checkSequence(user_sequence))
        {
            std::cout << "You win!" << std::endl;
        }
        else
        {
            std::cout << "You lose!" << std::endl;
        }






    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    Mix_CloseAudio();
    return 0;
}
