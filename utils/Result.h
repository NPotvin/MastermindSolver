#ifndef MASTERMINDSOLVER_RESULT_H
#define MASTERMINDSOLVER_RESULT_H

#include "Guess.h"
#include "Similarity.h"


class Result {
private:

    const Similarity _sim;
    const Guess _guess;

public:
    explicit Result() : _sim(), _guess() {}
    explicit Result(const Guess& solution, const Guess& candidate) :
            _sim(solution.computeDistanceTo(candidate)),
            _guess(candidate)
            {}

    //const Similarity& getSim() const {return _sim;}
    const unsigned& getPerfect() const {return _sim.getPerfect();}
    const unsigned& getColorOnly() const {return _sim.getColorOnly();}
    const Guess& getGuess() const {return _guess;}
} ;

#endif //MASTERMINDSOLVER_RESULT_H
