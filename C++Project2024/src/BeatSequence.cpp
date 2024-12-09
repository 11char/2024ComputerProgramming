#include "BeatSequence.h"
#include <iostream>


BeatSequence::BeatSequence(const std::vector<int>& intSequence, const std::string& soundPath)
        : sequence(intSequence), beat(std::make_shared<Beat>('C', soundPath)) {
    beat->loadSound();
}
BeatSequence::BeatSequence(const BeatSequence& other)
        : sequence(other.sequence), beat(other.beat) {}

BeatSequence::BeatSequence(BeatSequence&& other) noexcept
        : sequence(std::move(other.sequence)), beat(std::move(other.beat)) {}

BeatSequence& BeatSequence::operator=(const BeatSequence& other) {
    if (this != &other) {
        sequence = other.sequence;
        beat = other.beat;
    }
    return *this;
}

BeatSequence::~BeatSequence() {
    std::cout << "BeatSequence destructor called" << std::endl;
}

void BeatSequence::playSequence(int bpm, int channel) const {
    // Play each beat in the sequence

    for (const int& value : sequence) {
        beat->play(bpm, channel, value);
    }
}



BeatSequence& BeatSequence::operator=(BeatSequence&& other) noexcept {
    if (this != &other) {
        sequence = std::move(other.sequence);
        beat = std::move(other.beat);
    }
    return *this;
}
