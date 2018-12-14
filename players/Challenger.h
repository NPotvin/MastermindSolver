#ifndef MASTERMINDSOLVER_CHALLENGER_H
#define MASTERMINDSOLVER_CHALLENGER_H


#include <vector>
#include "../utils/Guess.h"
#include "../utils/Result.h"
#include "../utils/Color.h"

class Challenger {
private:

    std::vector<Guess> _guesses;

public:

    Challenger() : _guesses(0) {}
    Challenger(const size_t& begin, const size_t& end) {
        _guesses.reserve(end-begin);
        for (size_t i(begin); i<end; ++i)
            _guesses.emplace_back(Guess(i));
    }

    const Guess& getGuess() const {return _guesses[0];}
    const bool empty() const {return _guesses.empty();}

    /**
     * This method updates the plausibility of the guesses using this turn result.
     * The results of the past computations of the plausibility are kept in the
     * c_colorCount array of the Guess objects
     *
     * @param result : a Result object representing the result of this turn
     */
    void updatePlausibleGuesses(const Result& result) {
        for (size_t i(0); i<_guesses.size();) {
            Similarity currSim(_guesses[i].computeDistanceTo(result.getGuess()));
            if (_guesses[i] == result.getGuess() ||
                currSim.getPerfect() != result.getPerfect() ||
                currSim.getColorOnly() != result.getColorOnly()
                ) {
                // removing the guess i
                for (size_t j(i); j<_guesses.size()-1; ++j)
                    _guesses[j] = _guesses[j+1];
                _guesses.pop_back();
            }
            else
                i++;
        }
    }
};


#endif //MASTERMINDSOLVER_CHALLENGER_H
