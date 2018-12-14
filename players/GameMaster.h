#ifndef MASTERMINDSOLVER_GAMEMASTER_H
#define MASTERMINDSOLVER_GAMEMASTER_H


#include "../utils/Guess.h"
#include "../utils/Result.h"
#include <stdlib.h>

class GameMaster {
private:

    const Guess _solution;
    bool _finished;

public:

    GameMaster(const GameMaster&) = delete;
    explicit GameMaster() : _solution(rand()%GUESS_NUM()), _finished(false) {}

    const bool isGameFinished() const {return _finished;}

    /**
     * This method picks a guess at random among thoses sent by the players
     * and builds a Result object with it
     *
     * @param guesses a vector of Guess objects
     * @return a Result object
     */
    const Result manageGuesses(const std::vector<Guess>& guesses) {
        Result res(_solution, guesses[rand() % guesses.size()]);
        _finished = res.getPerfect() == GUESS_SIZE();
        return res;
    }

    void printSol() const {
        std::cout << "Picked solution is: ";
        _solution.print();
        std::cout<<std::endl;
    }
};


#endif //MASTERMINDSOLVER_GAMEMASTER_H
