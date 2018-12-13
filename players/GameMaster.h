#ifndef MASTERMINDSOLVER_GAMEMASTER_H
#define MASTERMINDSOLVER_GAMEMASTER_H


#include "../utils/Guess.h"
#include "../utils/Result.h"

class GameMaster {
private:

    const Guess _solution;
    bool _finished;

public:

    GameMaster(const GameMaster&) = delete;
    explicit GameMaster() : _solution(rand()%GUESS_NUM()), _finished(false) {}

    const bool isGameFinished() const {return _finished;}

    const Result manageGuesses(const std::vector<Guess>& guesses) {
        Result res(_solution, guesses[rand() % guesses.size()]);
        _finished = res.getPerfect() == GUESS_SIZE();
        return res;
    }

    void printSol() const {
      for (size_t i(0) ; i < GUESS_SIZE() ; ++i) {
        std::cout << _solution[i].getColorID() << " ";
      }
      std::cout << std::endl;
    }
};


#endif //MASTERMINDSOLVER_GAMEMASTER_H
