#ifndef MASTERMINDSOLVER_GAMEMASTER_H
#define MASTERMINDSOLVER_GAMEMASTER_H


#include <stdlib.h>
#include "../utils/Guess.h"
#include "../utils/Result.h"

class GameMaster {
private:

    const Guess _solution;
    bool _finished;


public:

    GameMaster(const GameMaster&) = delete;
    explicit GameMaster() : _solution(rand() % GUESS_NUM()), _finished(false) {}

    const bool isGameFinished() const {return _finished;}

    const Result manageGuesses(const Guess * const& guesses, const size_t& size) {
        Result res(_solution, guesses[rand() % size]);
        _finished = res.getPerfect() == GUESS_SIZE();
        return res;
    }
};


#endif //MASTERMINDSOLVER_GAMEMASTER_H
