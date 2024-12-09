//
// Created by Dachan Seo on 2024/11/18.
//

#include "SequenceGenerator.h"

SequenceGenerator::SequenceGenerator() {
    // Constructor (no initialization needed here)
}

std::vector<int> SequenceGenerator::generateRandomSequence(int beats) {
    std::vector<int> sequence;
    int totalBeats = beats * 12; // Convert beats from quarter to 1/48 notes
    int remainingBeats = totalBeats;
    while (remainingBeats > 0) {
        int multiple = getRandomMultiple();

        // Ensure the chosen multiple does not exceed the remaining beats
        if (multiple > remainingBeats) {
            multiple = remainingBeats;
        }
        if (remainingBeats < 3) {
            if (!sequence.empty()) {
                // Adjust the last number in the sequence
                sequence.back() += remainingBeats;
            } else {
                // If this is the first number, set it to the remaining beats
                sequence.push_back(remainingBeats);
            }
            break;
        }
        sequence.push_back(multiple);
        remainingBeats -= multiple;
    }
    return sequence;
}


std::vector<int> SequenceGenerator::generateMetronome(int beats){
    std::vector<int> sequence;
    for(int i =0; i<beats; i++) {
        sequence.push_back(12);
    }
    return sequence;
}
int SequenceGenerator::getRandomMultiple() {
    // Randomly choose between 3 and 4
    int base = (std::rand() % 2 == 0) ? 3 : 4;

    // Generate a random multiple (e.g., 3n or 4n)
    int multiplier = (std::rand() % 3) + 1; // Generate n in range [1, 3]
    return base * multiplier;
}

SequenceGenerator::~SequenceGenerator() {
    // Destructor: No explicit cleanup needed
}