#ifndef MASTERMINDSOLVER_CHALLENGER_H
#define MASTERMINDSOLVER_CHALLENGER_H


#include <vector>
#include "../utils/Guess.h"
#include "../utils/Color.h"
#include "../utils/Result.h"

class Challenger {
private:

    const unsigned _mask = 0;

    const std::vector<Guess> _guesses;

public:

    explicit Challenger(const size_t& id) : _mask(Color::getColorMask(id)), _guesses(std::vector<Guess>(0)) {
        // TODO determine the size of the guess vector in the init list (depends on the way we generate the mask)
        // TODO generate guesses
    }

    const Guess& getGuess() const {
        if (_guesses.empty())
            ;// TODO return an error to the game master
        return _guesses[0];
    }

    void manageResult(const Result& result) {
        // TODO use mask to determine if the result concerns our guesses
        // TODO remove the guesses that are no longer plausible
    }
};


#endif //MASTERMINDSOLVER_CHALLENGER_H
