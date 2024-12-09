#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "BeatSequence.h"
#include "SequenceGenerator.h"

class GameController {
private:
    BeatSequence beatSequence;
    BeatSequence beatMetronome;
    SequenceGenerator sequenceGenerator;
    std::vector<int> sequence;
    int sequenceLength;
    int bpm;

public:
    GameController(int sequenceLength, int bpm);
    void createThread();
    void playSequence() const;
    bool checkSequence(const std::vector<int>& user_sequence) const;
    void printSequence() const;
};

#endif // GAMECONTROLLER_H