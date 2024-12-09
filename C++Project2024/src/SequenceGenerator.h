//
// Created by Dachan Seo on 2024/11/18.
//

#ifndef C__PROJECT2024_SEQUENCEGENERATOR_H
#define C__PROJECT2024_SEQUENCEGENERATOR_H

#include <vector>
#include <random>

class SequenceGenerator{
public:
// Constructor
SequenceGenerator();

// Generate a sequence of floats such that the sum equals the given integer beats
std::vector<int> generateRandomSequence(int beats);
std::vector<int> generateMetronome(int beats);

// Destructor
~SequenceGenerator();
private:
    int getRandomMultiple();

};


#endif //C__PROJECT2024_SEQUENCEGENERATOR_H
