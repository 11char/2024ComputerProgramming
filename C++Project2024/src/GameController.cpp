#include "GameController.h"
#include <iostream>
#include <thread>

GameController::GameController(int sequenceLength, int bpm)
: beatSequence(std::vector<int>(),"../sound/beat_C.wav"),
beatMetronome (std::vector<int>(),"../sound/beat_C.wav"),
sequenceGenerator() {
    this->sequenceLength = sequenceLength;
    this->bpm = bpm;
    createThread();


}
void GameController::createThread() {
    sequence = sequenceGenerator.generateRandomSequence(sequenceLength);
    std::vector<int> metronome = sequenceGenerator.generateMetronome(sequenceLength);
    beatSequence = BeatSequence(sequence, "../sound/beat_C.wav");
    beatMetronome = BeatSequence(metronome, "../sound/beat_B.wav");
}
void GameController::playSequence() const {
    std::thread sequenceThread(&BeatSequence::playSequence, &beatSequence, bpm, 1);
    std::thread metronomeThread(&BeatSequence::playSequence, &beatMetronome, bpm, 2);
    sequenceThread.join();
    metronomeThread.join();
}
bool GameController::checkSequence(const std::vector<int>& user_sequence) const{
    return sequence==user_sequence;
}

void GameController::printSequence() const {
    std::cout << "Sequence: ";
    for (int num : sequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

