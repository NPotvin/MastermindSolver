#ifndef MASTERMINDSOLVER_RESULT_H
#define MASTERMINDSOLVER_RESULT_H

#include "Guess.h"


class Result {
public:

  const Similarity similarity;
  const Guess guess;

  explicit Result(const Guess& candSol, const Guess& other) : similarity(candSol.computeDistanceTo(other)), guess(other) {}



} ;

#endif //MASTERMINDSOLVER_RESULT_H
