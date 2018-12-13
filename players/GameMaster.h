#ifndef MASTERMINDSOLVER_GAMEMASTER_H
#define MASTERMINDSOLVER_GAMEMASTER_H


#include <random>
#include "../utils/Guess.h"
#include "../utils/Result.h"

class GameMaster {
private:

    const Guess _solution;
    bool _finished;
    std::random_device& _rand;

    const unsigned rand(const unsigned& mod) {return _rand()%mod;}
    const size_t rand(const size_t& mod) {return _rand()%mod;}

public:

    GameMaster(const GameMaster&) = delete;
    explicit GameMaster(std::random_device& rDevice) : _rand(rDevice), _solution(rand(GUESS_NUM())), _finished(false) {}

    const bool isGameFinished() const {return _finished;}

    const Result manageGuesses(const Guess * const& guesses, const size_t& size) {
        Result res(_solution, guesses[rand(size)]);
        _finished = res.getPerfect() == GUESS_SIZE();
        return res;
    }
};


#endif //MASTERMINDSOLVER_GAMEMASTER_H
