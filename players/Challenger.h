#ifndef MASTERMINDSOLVER_CHALLENGER_H
#define MASTERMINDSOLVER_CHALLENGER_H


#include <vector>
#include "../utils/Guess.h"
#include "../utils/Result.h"
#include "../utils/Color.h"

class Challenger {
private:

    const unsigned _mask = 0;

    std::vector<Guess> _guesses;

public:

    Challenger() {
        // TODO determine the size of the guess vector in the init list (depends on the way we generate the mask)
        // TODO generate guesses
    }

    const Guess& getGuess() const {
        if (_guesses.empty())
            ;// TODO return an error to the game master
        return _guesses[0];
    }

    void updatePlausibleGuesses(const Result& result) {
        for (size_t i(0); i<_guesses.size();) {
            Similarity currSim(_guesses[i].computeDistanceTo(result.guess));
            if (_guesses[i] == result.guess || currSim.perfect < result.sim.perfect || currSim.colorOnly < result.sim.colorOnly)
                _guesses.erase(_guesses.begin()+i);
            else
                i++;
        }
    }
};


#endif //MASTERMINDSOLVER_CHALLENGER_H
