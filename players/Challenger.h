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
        for (std::vector<Guess>::iterator it = _guesses.begin() ; it != _guesses.end() ; ++it) {
          Similarity currSim((*it).computeDistanceTo(result.guess)) ;
          if (*it == result.guess || currSim.perfect < result.sim.perfect || currSim.colorOnly < result.sim.colorOnly) {
            _guesses.erase(it);
          }
        }
    }
};


#endif //MASTERMINDSOLVER_CHALLENGER_H
