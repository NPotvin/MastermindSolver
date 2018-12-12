#ifndef MASTERMINDSOLVER_RESULT_H
#define MASTERMINDSOLVER_RESULT_H

#include "Guess.h"

typedef struct Result {
    const unsigned perfect;
    const unsigned colorOnly;
    const Guess guess;
} Result;

#endif //MASTERMINDSOLVER_RESULT_H
