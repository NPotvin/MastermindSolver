#ifndef MASTERMINDSOLVER_RESULT_H
#define MASTERMINDSOLVER_RESULT_H

#include "Guess.h"


class Result {
public:

  const Similarity sim;
  const Guess guess;

  explicit Result(const Guess& candSol, const Guess& other) : sim(candSol.computeDistanceTo(other)), guess(other) {}



} ;

#endif //MASTERMINDSOLVER_RESULT_H
