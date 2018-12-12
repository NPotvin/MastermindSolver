#ifndef MASTERMINDSOLVER_GAMEMASTER_H
#define MASTERMINDSOLVER_GAMEMASTER_H


#include <random>
#include "../utils/Guess.h"
#include "../utils/Result.h"

class GameMaster {
private:

    const Guess _solution;
    bool _finished;
    static std::random_device _rand;

    const unsigned rand(const unsigned& mod) {return _rand()%mod;}
    const size_t rand(const size_t& mod) {return _rand()%mod;}

public:

    GameMaster() : _solution(rand(GUESS_NUM())), _finished(false) {}

    const bool isGameFinished() const {return _finished;}

    const Result manageGuesses(const std::vector<Guess>& guesses) {
        Result res(guesses[rand(guesses.size())], _solution);
        _finished = res.getPerfect() == GUESS_NUM();
        return res;
    }
};


#endif //MASTERMINDSOLVER_GAMEMASTER_H
