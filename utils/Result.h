#ifndef MASTERMINDSOLVER_RESULT_H
#define MASTERMINDSOLVER_RESULT_H

#include "Guess.h"
#include "Similarity.h"


class Result {
private:

    const Similarity _sim;
    const Guess _guess;

public:

    explicit Result(const Guess& candSol, const Guess& other) : _sim(candSol.computeDistanceTo(other)), _guess(other) {}

    //const Similarity& getSim() const {return _sim;}
    const unsigned& getPerfect() const {return _sim.getPerfect();}
    const unsigned& getColorOnly() const {return _sim.getColorOnly();}
    const Guess& getGuess() const {return _guess;}
} ;

#endif //MASTERMINDSOLVER_RESULT_H
