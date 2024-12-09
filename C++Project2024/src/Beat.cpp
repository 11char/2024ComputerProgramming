#include "Beat.h"
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>
#include <utility>

//default constructor

Beat::Beat() : symbol('\0'), soundFile(""), sound(nullptr) {};
//constructor
Beat::Beat(char symbol, const std::string&  soundFile)
        : symbol(symbol), soundFile(std::move(soundFile)), sound(nullptr) {
}

Beat::Beat(const Beat& other)
        : symbol(other.symbol), soundFile(other.soundFile), sound(nullptr) {
    std::cout << "Beat copy constructor called for symbol: " << symbol << std::endl;
    if (other.sound) {
        sound = Mix_LoadWAV(soundFile.c_str());
        if (!sound) {
            std::cerr << "Failed to load sound: " << soundFile << " - " << Mix_GetError() << std::endl;
            throw std::runtime_error("Failed to load sound: " + soundFile + " - " + Mix_GetError());
        }
    }
}

Beat& Beat::operator=(const Beat& other) {
    std::cout << "Beat copy assignment operator called for symbol: " << symbol << std::endl;
    if (this == &other) {
        return *this;
    }

    if (sound) {
        Mix_FreeChunk(sound);
    }

    symbol = other.symbol;
    soundFile = other.soundFile;
    sound = nullptr;

    if (other.sound) {
        sound = Mix_LoadWAV(soundFile.c_str());
        if (!sound) {
            std::cerr << "Failed to load sound: " << soundFile << " - " << Mix_GetError() << std::endl;
            throw std::runtime_error("Failed to load sound: " + soundFile + " - " + Mix_GetError());
        }
    }

    return *this;
}

void Beat::loadSound() {
    if (sound) {
        //clear sound
        Mix_FreeChunk(sound);
        sound = nullptr;
    }
    sound = Mix_LoadWAV(soundFile.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound: " << soundFile << " - " << Mix_GetError() << std::endl;
        throw std::runtime_error("Failed to load sound: " + soundFile + " - " + Mix_GetError());
    }
}

void Beat::play(int bpm, int channel, int length) const {
    // Play the sound on any available channel no loop, sound not expected to exceed maximum duration

    if (!sound) {
        std::cerr << "Sound is not loaded" << std::endl;
        throw std::runtime_error("Sound is not loaded");
    }

    if (Mix_PlayChannel(channel, sound, 0) == -1) {
        throw std::runtime_error("Failed to play sound: " + std::string(Mix_GetError()));
    }

    int durationMs = (int) (60000 / bpm * length/12);
    if (channel == -1) {
        throw std::runtime_error("Failed to play sound: " + std::string(Mix_GetError()));
    }
    // Wait for the specified duration
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    // Stop the sound after the duration
    Mix_HaltChannel(channel);
}

char Beat::getSymbol() const {
    return symbol;
}
 Mix_Chunk* Beat::getSound() const {
     return sound;
 }

Beat::~Beat() {
    std::cout << "Beat destructor called for symbol: " << symbol << std::endl;
    if (sound) {
        Mix_FreeChunk(sound);
        sound = nullptr;
        std::cout << "Sound freed for file: " << soundFile << std::endl;
    }else{
        std::cout << "already freed for file: " << soundFile << std::endl;
    }
}