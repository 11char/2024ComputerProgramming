#ifndef BEAT_H
#define BEAT_H

#include <string>
#include <SDL.h>
#include <SDL_mixer.h>

class Beat {
private:
    char symbol;
    std::string soundFile;
    Mix_Chunk* sound;

public:
    Beat();
    Beat(char symbol, const std::string&  soundFile);
    Beat(const Beat& other);
    Beat& operator=(const Beat& other);
    void loadSound();
    void play(int bpm, int channel, int length) const;
    Mix_Chunk* getSound() const;
    char getSymbol() const;
    ~Beat();

};

#endif // BEAT_H