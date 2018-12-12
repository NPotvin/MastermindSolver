#include "Guess.h"


const Similarity Guess::computeDistanceTo(const Guess& other) const {
    unsigned perfect(0), colorOnly(0);

    for (size_t i(0); i < N_COLORS(); ++i) {
        colorOnly += std::min(_colorCount[i], other.getColorCount(i));
    }
    for (size_t i(0); i < GUESS_SIZE(); ++i){
        if (_guess[i] == other[i]) {
            perfect++;
            colorOnly--;
        }
    }
    return Similarity {
            perfect,
            colorOnly
        };
}
