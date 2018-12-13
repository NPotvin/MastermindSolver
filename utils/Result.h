#ifndef MASTERMINDSOLVER_RESULT_H
#define MASTERMINDSOLVER_RESULT_H

#include "Guess.h"
#include "Similarity.h"


class Result {
private:

    Similarity _sim;
    Guess _guess;

public:
    explicit Result() : _sim(), _guess() {}
    explicit Result(const Guess& solution, const Guess& candidate) :
            _sim(solution.computeDistanceTo(candidate)),
            _guess(candidate)
            {}
    Result(const Result& other) {
        _sim = other._sim;
        _guess = other._guess;
    }

    const unsigned& getPerfect() const {return _sim.getPerfect();}
    const unsigned& getColorOnly() const {return _sim.getColorOnly();}
    const Guess& getGuess() const {return _guess;}
} ;

#endif //MASTERMINDSOLVER_RESULT_H
