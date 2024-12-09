#ifndef BEATSEQUENCE_H
#define BEATSEQUENCE_H

#include "Beat.h"
#include <vector>
#include <string>
#include <memory>

class BeatSequence {
private:
    std::vector<int> sequence;
    std::shared_ptr<Beat> beat;
public:
    BeatSequence(const std::vector<int>& seq, const std::string& soundPath);
    BeatSequence(const BeatSequence& other);
    BeatSequence(BeatSequence&& other) noexcept;
    BeatSequence& operator=(const BeatSequence& other);
    BeatSequence& operator=(BeatSequence&& other) noexcept;
    ~BeatSequence();

    void playSequence(int bpm, int channel) const;

};

#endif // BEATSEQUENCE_H